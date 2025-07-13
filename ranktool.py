import easyocr
import numpy as np
import mss
import re
import pandas as pd
import time

reader = easyocr.Reader(['ko', 'en'])  # 한글 + 영어
df = pd.DataFrame(columns=["닉네임", "점수"])

flag_ifwin = False
flag_win_start = False
flag_win_end = False

try:
    with mss.mss() as sct:
        # Initial settings
        LeftPos = 1391
        TopPos = 180
        RightPos = 1920
        BottomPos = 222

        LeftPos2 = 1391
        TopPos2 = 306
        RightPos2 = 1920
        BottomPos2 = 350
        
        monitor_area = {"top": TopPos, "left": LeftPos, "width": RightPos - LeftPos, "height": BottomPos - TopPos}
        monitor_area2 = {"top": TopPos2, "left": LeftPos2, "width": RightPos2 - LeftPos2, "height": BottomPos2 - TopPos2}

        score = 0
        list_winner = []

        arr_ifwin = ['우승시', '우승세', '윤승세', '운승시']
        arr_win = ['승리', '승례']

        while True:
            img = np.array(sct.grab(monitor_area))[:, :, :3]
            img2 = np.array(sct.grab(monitor_area2))[:, :, :3]

            result = reader.readtext(img, detail=0)
            result2 = reader.readtext(img2, detail=0)

            words = []
            for line in result:
                words.extend(line.split())
            for line in result2:
                words.extend(line.split())
            print(words)

            # 1. "우승시" 찾음
            if any(any(key in text for key in arr_ifwin) for text in words):
                print("✅ 우승시 또는 유사 텍스트 감지됨!")
                flag_ifwin = True
                for word in words:
                    # "점" 으로 문자가 끝남
                    if word.endswith("점"):
                        # 점 앞의 숫자 추출
                        match = re.match(r"(\d+)(?=점$)", word)
                        if match:
                            score = int(match.group(1))
                            print("점수:", score)
                            break
            
            # 2. "승리" 찾음
            if not flag_win_end:
                local_isfindwin = False
                for i, word in enumerate(words):
                    # 승리 찾음
                    if any(key in word for key in arr_win):
                        flag_win_start = True
                        local_isfindwin = True
                        print("✅ 승리 또는 유사 텍스트 감지됨!")
                        if i > 0:
                            winner = words[i - 1]
                            print("우승자:", winner)
                            list_winner.append(winner)
                        break
                    # 점수 찾음
                    # TBD
                # "승리" 못찾음
                if flag_win_start and not local_isfindwin:
                    print("못찾음")
                    flag_win_start = False
                    flag_win_end = True
            
            # 3. 저장
            if flag_ifwin and flag_win_end:
                print("저장중...")
                df.loc[len(df)] = [max(set(list_winner), key=list_winner.count), score]
                flag_ifwin = False
                flag_win_end = False

except KeyboardInterrupt:
    # 출력
    print(df)