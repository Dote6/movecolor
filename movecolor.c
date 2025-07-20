variables
{
	global:
		0: SphereLocations
		1: Colours
		2: CorrectColour
		3: RoundNumber
		4: DetermineColourTrigger
		5: ArenaCentre
		6: ArenaRadius
		7: stringPick
		8: TiebreakerTrigger
		9: SphereID
		10: RaceTrigger
		11: HUDID
		12: LivingPlayers
		13: NextRoundTrigger
		14: ArenaID
		15: DynamicTrigger
		26: couple_list
		27: BLH
		28: HUDR
		29: HUDS
		30: RANK
		31: RANKER
		32: DH
		33: MRSO
		34: MRSS
		35: JQC
		36: INDEX
		37: K_ALREADYUSED_R
		38: COUPLE_1
		39: TRUE_VECTOR
		40: K_ALREADYUSED
		41: COUPLE_2
		42: theta
		43: rightindex
		44: COUPLE_3
		45: COUPLE_4
		46: door_count
		47: GD_playerarray
		48: door_effect2
		49: door_effect3
		50: door_effect4
		51: door_effect5
		52: door_effect6
		53: door_count_effect
		54: COUPLE_5
		55: COUPLE_6
		56: SOLO
		57: survive_player_array
		58: death_player_array
		59: rosecell
		60: consolation_trigger
		61: target_player
		62: consolation_effect
		63: death_count
		64: consolation_on
		65: consolation_only_once
		66: colorchange
		67: sombra_hide
		68: match_time_hud
		69: px
		70: py
		71: pz
		72: jsinangle
		73: cosangle
		74: parameter
		75: junoult_flag
		76: junotarget
		77: bati_theta
		78: KING
		79: king_triggered

	player:
		0: p_CurrentMode
		1: p_ModeTitle
		2: p_ModeIdeaOwner
		26: M2
		27: ZR1
		28: ZR2
		29: ZR3
		30: ZR4
		31: ZRV
		32: BAS1
		33: HANA1
		34: ECHO1
		35: HOG1
		36: MER
		37: GD
		38: SA
		39: G_GAGE
		40: MD
		41: G_GAGE_H
		42: ILL1
		43: ILL2
		44: ILL3
		45: ILL4
		46: ILL5
		47: ZRC
		48: consolation_survive
		49: ZYTGAGE
		50: ALT
		51: HZMODE
		52: HZQ
		53: RANKER
		54: Kiriko_Tele
		55: MV
		56: MSDP
		57: Z_GAGE_H
		58: JQC_GAGE
		59: SJ_SL
		60: RV_GAGE
		61: KRK_CELL1
		62: KRK_C1
		63: HOGBL
		64: LASTDMGPLAYER
		65: playerCarried
		66: p_kill
		67: thrower
		68: closeToPlayer
		69: isChasing
		70: mercypassive_once
		71: hana_count
		72: rein_lock
		73: howtoplay
		74: howtoplayV1
		75: howtoplayV2
		76: mauga_effect1
		77: mauga_effect2
		78: mauga_effect3
		79: mauga_effect4
		80: random_vector
		81: was_kinged
		82: Out_side
		83: aim_vector
		84: aim_vector_
		85: unit_vector_
		86: klm_
		87: left_end_
		88: right_end_
		89: left_end
		90: toohigh
		91: random_cell
		92: mauga_effect5
		93: mauga_effect6
		94: Jump1
		95: Jump2
		96: cell_index
		97: on_train
		98: can_knife
		99: mauga_effect7
		100: mauga_effect8
		101: TOR_FIRED
		102: TOR_EFFECT1
		103: TOR_EFFECT2
		104: TOR_EFFECT3
		105: ttek_effect
		106: ttek_text
		107: ttek_trigger
		108: ttek_left_enable
		109: ttek_right_enable
		110: WRF
		111: DVQ
		112: KRK_CELL2
		113: queen_var
		114: queen_time
		115: queen_t
		116: junk_var
}

subroutines
{
	0: OutsidePenalty
	7: SombraHide
	8: Ttek_LeftClick
	9: Ttek_RightClick
	10: Map2
	11: QUEEN_END_COND
	12: QUEEN_COL_CNG
	13: BATI_TEL_TRIGGER
	14: TTEK_TRIGGER
	15: TTEK_KING
}

rule("초기 세팅 및 게임 설명 HUD (수정)")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Is Game In Progress == True;
		Is Assembling Heroes == False;
		Global.RoundNumber == 0;
	}

	action
	{
		"초기 변수"
		Global.JQC = 0;
		All Players(All Teams).Out_side = 0;
		"초기 세팅"
		Global.Colours = Empty Array;
		Global.SphereID = Empty Array;
		Disable Built-In Game Mode Announcer;
		Disable Game Mode In-World UI(All Players(All Teams));
		Disable Game Mode HUD(All Players(All Teams));
		Disable Built-In Game Mode Scoring;
		Disable Built-In Game Mode Respawning(All Players(All Teams));
		Disable Built-In Game Mode Completion;
		Enable Death Spectate Target HUD(All Players(All Teams));
		Enable Death Spectate All Players(All Players(All Teams));
		Disable Built-In Game Mode Music;
		"구역 설정"
		Global.Z = Round To Integer(X Component Of(Nearest Walkable Position(Vector(100, 100, 100))), To Nearest);
		Wait(0.250, Ignore Condition);
		Teleport(All Players(All Teams), Global.ArenaCentre + Vector(0, 12, 0));
		Global.LivingPlayers = All Players(All Teams);
		"게임 설명"
		Create HUD Text(All Players(All Teams), Custom String("{0} 라운드 / 생존 인원 : {1}명 {2}", Global.RoundNumber, Number Of Living Players(
			All Teams), Ability Icon String(Hero(메르시), Button(Ability 1))), Null, Null, Top, 0, Color(흰색), Color(흰색), Color(흰색), String,
			Default Visibility);
		Global.HUDR = Last Text ID;
		Create HUD Text(All Players(All Teams), Custom String("제작 : KISUM / 250712 ver\r"), Custom String(
			" originator : THEFOOT\r, 파이리\r\n special thx : Dote6, YaksuStn\r\n server load : {0}\r\n {1} {2}번째 구역", Custom String(
			"{0} | {1}", Server Load, Server Load Average), Current Map, 1 + Global.ArenaID), Custom String(
			" the latest code : 69033                              "), Left, -2, Color(Orange), Color(흰색), Color(흰색), String,
			Visible Always);
		Create HUD Text(All Players(All Teams), Null, Custom String("   "), Null, Left, 0, Color(Green), Color(Green), Color(흰색), None,
			Visible Always);
		Create HUD Text(All Players(All Teams), Null, Null, Custom String("색깔따라 이동하기 룰설명 : 근접공격 + {0} (ON/OFF)", Input Binding String(
			Button(Secondary Fire))), Right, -10, Color(흰색), Color(흰색), Color(흰색), Visible To and String, Visible Always);
		Create HUD Text(All Players(All Teams), Null, Custom String("{0}\r\n{1}\r", Custom String(
			"[신규 영웅 추가] 사기 영웅 프레야를 지금 바로 만나보세요!\r\n600여 명의 실시간 순위 확인하기 ▶ https://url.kr/sjvkhm"), Custom String(
			"{0} 건의/제보 : 카카오톡 오픈채팅방에 색깔따라 이동하기 검색 {0}\r", Icon String(Diamond), Ability Icon String(Hero(일리아리), Button(Ultimate)))), Null,
			Right, -9, Color(흰색), Color(흰색), Color(흰색), None, Visible Always);
		Create HUD Text(All Players(All Teams), Null, Custom String("   "), Null, Right, -6, Color(Green), Color(Green), Color(흰색), None,
			Visible Always);
		Create HUD Text(All Players(All Teams), Null, Custom String("   "), Null, Right, 1, Color(Green), Color(Green), Color(흰색), None,
			Visible Always);
		Wait(1.500, Ignore Condition);
		Small Message(All Players(All Teams), Custom String("♥KISUM과 함께하는 색깔따라 이동하기♥"));
		Wait(1, Ignore Condition);
		Small Message(All Players(All Teams), Custom String("제한시간 안에 우측 상단에 표시된 색깔 셀로 들어가세요!"));
		Wait(1, Ignore Condition);
		Small Message(All Players(All Teams), Custom String("최후에 남는 한명이 승리합니다!"));
		Global.NextRoundTrigger = 1;
		Global.RoundNumber = 1;
		Start Heal Over Time(All Players(All Teams), Null, 9999, 100);
		Wait(3, Ignore Condition);
		Abort If(Global.DynamicTrigger != 1);
	}
}

rule("Match Time 0")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Is In Setup == True;
	}

	action
	{
		Set Match Time(0);
	}
}

rule("Match Time 1")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		!(Match Time < 30) == True;
	}

	action
	{
		Destroy HUD Text(Global.match_time_hud);
		Create HUD Text(All Players(All Teams), Null, Null, Custom String("다음 라운드 준비중입니다!"), Top, -10, Null, Null, Color(Orange), String,
			Default Visibility);
		Global.match_time_hud = Last Text ID;
	}
}

rule("Match Time 2")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Match Time < 30;
	}

	action
	{
		Destroy HUD Text(Global.match_time_hud);
		Create HUD Text(All Players(All Teams), Null, Null, Custom String("남은 시간 : {0}.{1}초", Round To Integer(Match Time, Down) - 0,
			Round To Integer(10 * Match Time, Down) % 10), Top, -10, Null, Null, Color(Orange), String, Default Visibility);
		Global.match_time_hud = Last Text ID;
	}
}

rule("승자결정전 HUD")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.RoundNumber == 420.690;
	}

	action
	{
		Wait(0.100, Ignore Condition);
		Destroy HUD Text(Global.HUDR);
		Create HUD Text(All Players(All Teams), Custom String("승자결정전 / 생존 인원 : {1}명 {2}", Null, Number Of Living Players(All Teams),
			Ability Icon String(Hero(메르시), Button(Ability 1))), Null, Null, Top, 0, Color(흰색), Color(흰색), Color(흰색), String,
			Default Visibility);
	}
}

rule("승리 HUD [개별]")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Current Game Mode == Game Mode(데스매치);
		Is Game In Progress == True;
		Is Assembling Heroes != True;
		Count Of(Global.LivingPlayers) == 1;
	}

	action
	{
		Wait(2, Abort When False);
		Enable Built-In Game Mode Music;
		Enable Built-In Game Mode Announcer;
		Declare Player Victory(Global.LivingPlayers);
	}
}

rule("[패시브] : 모든 영웅 자동힐 / 트레이서 제외")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Start Heal Over Time(Filtered Array(All Players(All Teams), Current Array Element != Hero(트레이서)), Null, 9999, 100);
	}
}

rule("영웅 선택 시간")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Is Assembling Heroes == True;
	}

	action
	{
		Set Match Time(20);
	}
}

rule("Outside Rule Trigger by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Distance Between(Global.ArenaCentre, Event Player) > Global.ArenaRadius;
		Array Contains(Global.LivingPlayers, Event Player) == True;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

rule("[Sub] OutsidePenalty : Outside Rule Penalty by KISUM")
{
	event
	{
		Subroutine;
		OutsidePenalty;
	}

	action
	{
		Teleport(Event Player, Global.ArenaCentre + Vector(0, 12, 0));
		Wait(0.250, Ignore Condition);
		Event Player.Out_side = 0;
		Loop If(Global.RoundNumber < 3 && Distance Between(Event Player, Global.ArenaCentre) > Global.ArenaRadius);
		Abort If(Global.RoundNumber < 3 && Distance Between(Event Player, Global.ArenaCentre) < Global.ArenaRadius);
		Event Player.p_CurrentMode += 1;
		Set Status(Event Player, Null, Burning, Event Player.p_CurrentMode * 2);
		Set Status(Event Player, Null, Hacked, Event Player.p_CurrentMode * 2);
		Small Message(Event Player, Custom String("{0}초간 장외 패널티가 활성화 됩니다", Event Player.p_CurrentMode * 2));
		Wait(0.250, Abort When False);
		Loop If Condition Is True;
	}
}

rule("센터 비주얼 by KISUM")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Is Game In Progress == True;
		Is Assembling Heroes == False;
		Global.RoundNumber == 0;
	}

	action
	{
		Create Effect(All Players(All Teams), Light Shaft, Color(Yellow), Global.ArenaCentre + Vector(0, -10, 0), 0.075, None);
		Create In-World Text(All Players(All Teams), Custom String("{0} RANKING\r\n\r\n{1}\r", Icon String(Skull), Custom String(
			"11652 누구인\r\n10061 신월동1짱김정훈\r\n7456 KISUM\r\n7073 ww7865\r\n6595 전설\r\n6244 우아앙\r\n6121 Dote6\r\n5587 고9마9웠어\r\n5174 JUMP\r\n4631 YaksuStn")),
			Global.ArenaCentre + Vector(0, 25, 0), 1.750, Do Not Clip, None, Color(흰색), Default Visibility);
		Global.RANKER = -6;
	}
}

rule("플레이어 비주얼 L by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Array Contains(Array(Custom String("누구인"), Custom String("신월동1짱김정훈"), Custom String("KISUM")), Custom String("{0}", Event Player))
			== True;
	}

	action
	{
		Create HUD Text(All Players(All Teams), Null, Custom String("함께하고 있는 LEGEND : {1} {0}", Hero Icon String(Hero Of(Event Player)),
			Event Player, Icon String(Bolt)), Null, Right, 1.005, Null, Custom Color(255, 255 * Absolute Value(Sine From Degrees(
			Global.colorchange)), 0, 255), Null, Visible To String and Color, Default Visibility);
		Event Player.RANKER = Last Text ID;
	}
}

rule("플레이어 비주얼 CP by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Array Contains(Array(Custom String("ww7865"), Custom String("전설"), Custom String("우아앙")), Custom String("{0}", Event Player))
			== True;
	}

	action
	{
		Create HUD Text(All Players(All Teams), Null, Custom String("함께하고 있는 CHAMPION : {1} {0}", Hero Icon String(Hero Of(Event Player)),
			Event Player, Icon String(Bolt)), Null, Right, 1.010, Null, Custom Color(255, 255 * Absolute Value(Sine From Degrees(
			Global.colorchange)), 0, 255), Null, Visible To String and Color, Default Visibility);
		Event Player.RANKER = Last Text ID;
	}
}

rule("플레이어 비주얼 CL by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Array Contains(Array(Custom String("Dote6"), Custom String("고9마9웠어"), Custom String("JUMP"), Custom String("YaksuStn")),
			Custom String("{0}", Event Player)) == True;
	}

	action
	{
		Create HUD Text(All Players(All Teams), Null, Custom String("함께하고 있는 CHALLENGER : {1} {0}", Hero Icon String(Hero Of(
			Event Player)), Event Player), Null, Right, 1.015, Color(흰색), Color(Yellow), Color(Yellow), Visible To and String,
			Default Visibility);
		Event Player.RANKER = Last Text ID;
	}
}

rule("플레이어 비주얼 G by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Array Contains(Array(Custom String("상한푸딩"), Custom String("레니아트"), Custom String("양띵샌즈앤더맨"), Custom String("onmygod"),
			Custom String("하리보와젤리")), Custom String("{0}", Event Player)) == True;
	}

	action
	{
		Create HUD Text(All Players(All Teams), Null, Custom String("함께하고 있는 GRAND MASTER : {1} {0}", Hero Icon String(Hero Of(
			Event Player)), Event Player), Null, Right, 1.020, Color(흰색), Color(Yellow), Color(Yellow), Visible To and String,
			Default Visibility);
		Event Player.RANKER = Last Text ID;
	}
}

rule("플레이어 비주얼 M by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Array Contains(Array(Custom String("악동햄스터"), Custom String("A080A"), Custom String("tenmong"), Custom String("눈누난나"),
			Custom String("루니나")), Custom String("{0}", Event Player)) == True;
	}

	action
	{
		Create HUD Text(All Players(All Teams), Null, Custom String("함께하고 있는 MASTER : {1} {0}", Hero Icon String(Hero Of(Event Player)),
			Event Player), Null, Right, 1.030, Color(흰색), Color(Yellow), Color(Yellow), Visible To and String, Default Visibility);
		Event Player.RANKER = Last Text ID;
	}
}

rule("플레이어 비주얼 X by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Has Spawned(Event Player) == False;
	}

	action
	{
		Destroy In-World Text(Event Player.RANKER);
	}
}

rule("화염 상태")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Has Status(Event Player, Burning) == True;
	}

	action
	{
		Set Move Speed(Event Player, 45);
	}
}

rule("화염 상태 종료 (특전관련 수정)")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Has Status(Event Player, Burning) != True;
	}

	action
	{
		If(Hero Of(Event Player) == Players On Hero(Hero(토르비욘), All Teams));
			If(Event Player.ttek_right_enable == True);
				Set Move Speed(Event Player, 135);
			Else;
				Set Move Speed(Event Player, 90);
			End;
		Else If(Hero Of(Event Player) == Players On Hero(Hero(루시우), All Teams));
			Set Move Speed(Event Player, 111 + Global.RoundNumber * 9);
		Else;
			Set Move Speed(Event Player, 120);
		End;
	}
}

rule("Remove From Array When a Player Dies")
{
	event
	{
		Player Died;
		All;
		All;
	}

	condition
	{
		Array Contains(Global.LivingPlayers, Event Player) == True;
	}

	action
	{
		Global.LivingPlayers = Remove From Array(Global.LivingPlayers, Event Player);
		Abort If(!(Hero Of(Event Player) == Hero(D.Va)));
		Wait(2, Ignore Condition);
		Global.LivingPlayers = Remove From Array(Global.LivingPlayers, Event Player);
	}
}

rule("경기 진행 후 참여 1 by KISUM")
{
	event
	{
		Player Joined Match;
		All;
		All;
	}

	condition
	{
		Global.RoundNumber < 1;
	}

	action
	{
		Disable Built-In Game Mode Respawning(Event Player);
		Enable Death Spectate Target HUD(Event Player);
		Enable Death Spectate All Players(Event Player);
		Global.LivingPlayers = Append To Array(Global.LivingPlayers, Event Player);
		Set Player Score(Event Player, Global.RoundNumber);
		Event Player.Z = 0;
	}
}

rule("경기 진행 후 참여 2 by KISUM")
{
	event
	{
		Player Joined Match;
		All;
		All;
	}

	condition
	{
		Global.RoundNumber == 1;
		Match Time > 10;
	}

	action
	{
		Disable Built-In Game Mode Respawning(Event Player);
		Enable Death Spectate Target HUD(Event Player);
		Enable Death Spectate All Players(Event Player);
		Global.LivingPlayers = Append To Array(Global.LivingPlayers, Event Player);
		Set Player Score(Event Player, Global.RoundNumber);
		Event Player.Z = 0;
	}
}

rule("시간 내 영웅 미선택 1 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Global.RoundNumber == 1;
		Match Time <= 10;
		Has Spawned(Event Player) != True;
	}

	action
	{
		Event Player.Z = 1;
		Global.LivingPlayers = Remove From Array(Global.LivingPlayers, Event Player);
	}
}

rule("시간 내 영웅 미선택 2 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Global.RoundNumber > 1;
		Has Spawned(Event Player) != True;
	}

	action
	{
		Event Player.Z = 1;
		Global.LivingPlayers = Remove From Array(Global.LivingPlayers, Event Player);
	}
}

rule("늦은 참여 1 by KISUM")
{
	event
	{
		Player Joined Match;
		All;
		All;
	}

	condition
	{
		Is Game In Progress == True;
		Global.RoundNumber > 1;
	}

	action
	{
		Disable Built-In Game Mode Respawning(Event Player);
		Enable Death Spectate Target HUD(Event Player);
		Event Player.Z = 1;
	}
}

rule("늦은 참여 2 by KISUM")
{
	event
	{
		Player Joined Match;
		All;
		All;
	}

	condition
	{
		Is Game In Progress == True;
		Global.RoundNumber == 1;
		Match Time < 10;
	}

	action
	{
		Disable Built-In Game Mode Respawning(Event Player);
		Enable Death Spectate Target HUD(Event Player);
		Event Player.Z = 1;
	}
}

rule("시간 내 영웅 미선택 + 늦은 참여 사망 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Event Player.Z == 1;
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Set Ultimate Ability Enabled(Event Player, False);
		Wait(1, Ignore Condition);
		Enable Death Spectate All Players(Event Player);
		Kill(Event Player, Null);
		Big Message(Event Player, Custom String("다음 게임까지 잠시만 기다려 주세요!"));
		Wait(1, Abort When False);
		Loop If Condition Is True;
	}
}

rule("Player Leaves")
{
	event
	{
		Player Left Match;
		All;
		All;
	}

	condition
	{
		Is Game In Progress == True;
	}

	action
	{
		Global.LivingPlayers = Remove From Array(Global.LivingPlayers, Event Player);
	}
}

rule("Determine Correct Colour")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.DetermineColourTrigger == 1;
	}

	action
	{
		Wait(3.435, Abort When False);
		Global.CorrectColour = Random Value In Array(Array Slice(Global.Colours, 0, 6));
		Wait(0.016, Ignore Condition);
		Global.DetermineColourTrigger = 0;
	}
}

rule("First Sphere is White")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[0] == 1;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(흰색), Global.SphereLocations[0], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("First Sphere is Yellow")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[0] == 2;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Yellow), Global.SphereLocations[0], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("First Sphere is Green")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[0] == 3;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Green), Global.SphereLocations[0], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("First Sphere is Purple")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[0] == 4;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Purple), Global.SphereLocations[0], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("First Sphere is Red")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[0] == 5;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Red), Global.SphereLocations[0], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("First Sphere is Blue")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[0] == 6;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Blue), Global.SphereLocations[0], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("First Sphere is Orange")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[0] == 7;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Orange), Global.SphereLocations[0], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("First Sphere is Aqua")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[0] == 8;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Aqua), Global.SphereLocations[0], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Second Sphere is White")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[1] == 1;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(흰색), Global.SphereLocations[1], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Second Sphere is Yellow")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[1] == 2;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Yellow), Global.SphereLocations[1], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Second Sphere is Green")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[1] == 3;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Green), Global.SphereLocations[1], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Second Sphere is Purple")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[1] == 4;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Purple), Global.SphereLocations[1], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Second Sphere is Red")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[1] == 5;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Red), Global.SphereLocations[1], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Second Sphere is Blue")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[1] == 6;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Blue), Global.SphereLocations[1], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Second Sphere is Orange")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[1] == 7;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Orange), Global.SphereLocations[1], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Second Sphere is Aqua")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[1] == 8;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Aqua), Global.SphereLocations[1], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Third Sphere is White")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[2] == 1;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(흰색), Global.SphereLocations[2], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Third Sphere is Yellow")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[2] == 2;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Yellow), Global.SphereLocations[2], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Third Sphere is Green")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[2] == 3;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Green), Global.SphereLocations[2], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Third Sphere is Purple")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[2] == 4;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Purple), Global.SphereLocations[2], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Third Sphere is Red")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[2] == 5;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Red), Global.SphereLocations[2], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Third Sphere is Blue")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[2] == 6;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Blue), Global.SphereLocations[2], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Third Sphere is Orange")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[2] == 7;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Orange), Global.SphereLocations[2], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Third Sphere is Aqua")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[2] == 8;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Aqua), Global.SphereLocations[2], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Fourth Sphere is White")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[3] == 1;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(흰색), Global.SphereLocations[3], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Fourth Sphere is Yellow")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[3] == 2;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Yellow), Global.SphereLocations[3], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Fourth Sphere is Green")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[3] == 3;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Green), Global.SphereLocations[3], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Fourth Sphere is Purple")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[3] == 4;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Purple), Global.SphereLocations[3], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Fourth Sphere is Red")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[3] == 5;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Red), Global.SphereLocations[3], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Fourth Sphere is Blue")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[3] == 6;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Blue), Global.SphereLocations[3], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Fourth Sphere is Orange")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[3] == 7;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Orange), Global.SphereLocations[3], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Fourth Sphere is Aqua")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[3] == 8;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Aqua), Global.SphereLocations[3], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Fifth Sphere is White")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[4] == 1;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(흰색), Global.SphereLocations[4], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Fifth Sphere is Yellow")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[4] == 2;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Yellow), Global.SphereLocations[4], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Fifth Sphere is Green")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[4] == 3;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Green), Global.SphereLocations[4], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Fifth Sphere is Purple")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[4] == 4;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Purple), Global.SphereLocations[4], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Fifth Sphere is Red")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[4] == 5;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Red), Global.SphereLocations[4], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Fifth Sphere is Blue")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[4] == 6;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Blue), Global.SphereLocations[4], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Fifth Sphere is Orange")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[4] == 7;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Orange), Global.SphereLocations[4], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Fifth Sphere is Aqua")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[4] == 8;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Aqua), Global.SphereLocations[4], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Sixth Sphere is White")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[5] == 1;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(흰색), Global.SphereLocations[5], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Sixth Sphere is Yellow")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[5] == 2;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Yellow), Global.SphereLocations[5], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Sixth Sphere is Green")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[5] == 3;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Green), Global.SphereLocations[5], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Sixth Sphere is Purple")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[5] == 4;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Purple), Global.SphereLocations[5], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Sixth Sphere is Red")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[5] == 5;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Red), Global.SphereLocations[5], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Sixth Sphere is Blue")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[5] == 6;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Blue), Global.SphereLocations[5], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Sixth Sphere is Orange")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[5] == 7;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Orange), Global.SphereLocations[5], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Sixth Sphere is Aqua")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[5] == 8;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Aqua), Global.SphereLocations[5], 3, Position and Radius);
		Global.SphereID = Append To Array(Global.SphereID, Last Created Entity);
	}
}

rule("Display White")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.CorrectColour == 1;
	}

	action
	{
		Wait(0.250, Ignore Condition);
		Destroy HUD Text(Global.HUDID);
		If(Global.sombra_hide == 1);
			Call Subroutine(SombraHide);
		Else;
			If(Global.RoundNumber <= 20);
				Create HUD Text(All Living Players(All Teams), Custom String("{0}R : 하얀색 셀로 들어가세요!", Global.RoundNumber), Null, Null, Right, 0,
					Color(흰색), Color(흰색), Color(흰색), String, Default Visibility);
			Else;
				Create HUD Text(All Living Players(All Teams), Custom String("승자결정전 : 하얀색 셀로 들어가세요!", Global.RoundNumber), Null, Null, Right, 0,
					Color(흰색), Color(흰색), Color(흰색), String, Default Visibility);
			End;
			Global.HUDID = Last Text ID;
			Big Message(All Living Players(All Teams), Custom String("우측 상단에 새로운 색깔 셀이 제시되었습니다!"));
		End;
	}
}

rule("Display Yellow")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.CorrectColour == 2;
	}

	action
	{
		Wait(0.250, Ignore Condition);
		Destroy HUD Text(Global.HUDID);
		If(Global.sombra_hide == 1);
			Call Subroutine(SombraHide);
		Else;
			If(Global.RoundNumber <= 20);
				Create HUD Text(All Living Players(All Teams), Custom String("{0}R : 노란색 셀로 들어가세요!", Global.RoundNumber), Null, Null, Right, 0,
					Color(Yellow), Color(흰색), Color(흰색), String, Default Visibility);
			Else;
				Create HUD Text(All Living Players(All Teams), Custom String("승자결정전 : 노란색 셀로 들어가세요!", Global.RoundNumber), Null, Null, Right, 0,
					Color(Yellow), Color(흰색), Color(흰색), String, Default Visibility);
			End;
			Global.HUDID = Last Text ID;
			Big Message(All Living Players(All Teams), Custom String("우측 상단에 새로운 색깔 셀이 제시되었습니다!"));
		End;
	}
}

rule("Display Green")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.CorrectColour == 3;
	}

	action
	{
		Wait(0.250, Ignore Condition);
		Destroy HUD Text(Global.HUDID);
		If(Global.sombra_hide == 1);
			Call Subroutine(SombraHide);
		Else;
			If(Global.RoundNumber <= 20);
				Create HUD Text(All Living Players(All Teams), Custom String("{0}R : 초록색 셀로 들어가세요!", Global.RoundNumber), Null, Null, Right, 0,
					Color(Green), Color(흰색), Color(흰색), String, Default Visibility);
			Else;
				Create HUD Text(All Living Players(All Teams), Custom String("승자결정전 : 초록색 셀로 들어가세요!", Global.RoundNumber), Null, Null, Right, 0,
					Color(Green), Color(흰색), Color(흰색), String, Default Visibility);
			End;
			Global.HUDID = Last Text ID;
			Big Message(All Living Players(All Teams), Custom String("우측 상단에 새로운 색깔 셀이 제시되었습니다!"));
		End;
	}
}

rule("Display Purple")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.CorrectColour == 4;
	}

	action
	{
		Wait(0.250, Ignore Condition);
		Destroy HUD Text(Global.HUDID);
		If(Global.sombra_hide == 1);
			Call Subroutine(SombraHide);
		Else;
			If(Global.RoundNumber <= 20);
				Create HUD Text(All Living Players(All Teams), Custom String("{0}R : 보라색 셀로 들어가세요!", Global.RoundNumber), Null, Null, Right, 0,
					Color(Purple), Color(흰색), Color(흰색), String, Default Visibility);
			Else;
				Create HUD Text(All Living Players(All Teams), Custom String("승자결정전 : 보라색 셀로 들어가세요!", Global.RoundNumber), Null, Null, Right, 0,
					Color(Purple), Color(흰색), Color(흰색), String, Default Visibility);
			End;
			Global.HUDID = Last Text ID;
			Big Message(All Living Players(All Teams), Custom String("우측 상단에 새로운 색깔 셀이 제시되었습니다!"));
		End;
	}
}

rule("Display Red")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.CorrectColour == 5;
	}

	action
	{
		Wait(0.250, Ignore Condition);
		Destroy HUD Text(Global.HUDID);
		If(Global.sombra_hide == 1);
			Call Subroutine(SombraHide);
		Else;
			If(Global.RoundNumber <= 20);
				Create HUD Text(All Living Players(All Teams), Custom String("{0}R : 빨간색 셀로 들어가세요!", Global.RoundNumber), Null, Null, Right, 0,
					Color(Red), Color(흰색), Color(흰색), String, Default Visibility);
			Else;
				Create HUD Text(All Living Players(All Teams), Custom String("승자결정전 : 빨간색 셀로 들어가세요!", Global.RoundNumber), Null, Null, Right, 0,
					Color(Red), Color(흰색), Color(흰색), String, Default Visibility);
			End;
			Global.HUDID = Last Text ID;
			Big Message(All Living Players(All Teams), Custom String("우측 상단에 새로운 색깔 셀이 제시되었습니다!"));
		End;
	}
}

rule("Display Blue")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.CorrectColour == 6;
	}

	action
	{
		Wait(0.250, Ignore Condition);
		Destroy HUD Text(Global.HUDID);
		If(Global.sombra_hide == 1);
			Call Subroutine(SombraHide);
		Else;
			If(Global.RoundNumber <= 20);
				Create HUD Text(All Living Players(All Teams), Custom String("{0}R : 파란색 셀로 들어가세요!", Global.RoundNumber), Null, Null, Right, 0,
					Color(Blue), Color(흰색), Color(흰색), String, Default Visibility);
			Else;
				Create HUD Text(All Living Players(All Teams), Custom String("승자결정전 : 파란색 셀로 들어가세요!", Global.RoundNumber), Null, Null, Right, 0,
					Color(Blue), Color(흰색), Color(흰색), String, Default Visibility);
			End;
			Global.HUDID = Last Text ID;
			Big Message(All Living Players(All Teams), Custom String("우측 상단에 새로운 색깔 셀이 제시되었습니다!"));
		End;
	}
}

rule("Display Orange")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.CorrectColour == 7;
	}

	action
	{
		Wait(0.250, Ignore Condition);
		Destroy HUD Text(Global.HUDID);
		If(Global.sombra_hide == 1);
			Call Subroutine(SombraHide);
		Else;
			If(Global.RoundNumber <= 20);
				Create HUD Text(All Living Players(All Teams), Custom String("{0}R : 주황색 셀로 들어가세요!", Global.RoundNumber), Null, Null, Right, 0,
					Color(Orange), Color(흰색), Color(흰색), String, Default Visibility);
			Else;
				Create HUD Text(All Living Players(All Teams), Custom String("승자결정전 : 주황색 셀로 들어가세요!", Global.RoundNumber), Null, Null, Right, 0,
					Color(Orange), Color(흰색), Color(흰색), String, Default Visibility);
			End;
			Global.HUDID = Last Text ID;
			Big Message(All Living Players(All Teams), Custom String("우측 상단에 새로운 색깔 셀이 제시되었습니다!"));
		End;
	}
}

rule("Display Aqua")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.CorrectColour == 8;
	}

	action
	{
		Wait(0.250, Ignore Condition);
		Destroy HUD Text(Global.HUDID);
		If(Global.sombra_hide == 1);
			Call Subroutine(SombraHide);
		Else;
			If(Global.RoundNumber <= 20);
				Create HUD Text(All Living Players(All Teams), Custom String("{0}R : 하늘색 셀로 들어가세요!", Global.RoundNumber), Null, Null, Right, 0,
					Color(Aqua), Color(흰색), Color(흰색), String, Default Visibility);
			Else;
				Create HUD Text(All Living Players(All Teams), Custom String("승자결정전 : 하늘색 셀로 들어가세요!", Global.RoundNumber), Null, Null, Right, 0,
					Color(Aqua), Color(흰색), Color(흰색), String, Default Visibility);
			End;
			Global.HUDID = Last Text ID;
			Big Message(All Living Players(All Teams), Custom String("우측 상단에 새로운 색깔 셀이 제시되었습니다!"));
		End;
	}
}

rule("라운드 사이 색깔 구슬 미제시")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Match Time > 30;
		Match Time < 118.500;
	}

	action
	{
		Wait(0.250, Ignore Condition);
		Destroy HUD Text(Global.HUDID);
	}
}

rule("Determine Sphere 1 is Correct")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[0] == Global.CorrectColour;
	}

	action
	{
		Global.stringPick = Append To Array(Global.stringPick, Global.SphereLocations[0]);
	}
}

rule("Determine Sphere 2 is Correct")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[1] == Global.CorrectColour;
	}

	action
	{
		Global.stringPick = Append To Array(Global.stringPick, Global.SphereLocations[1]);
	}
}

rule("Determine Sphere 3 is Correct")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[2] == Global.CorrectColour;
	}

	action
	{
		Global.stringPick = Append To Array(Global.stringPick, Global.SphereLocations[2]);
	}
}

rule("Determine Sphere 4 is Correct")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[3] == Global.CorrectColour;
	}

	action
	{
		Global.stringPick = Append To Array(Global.stringPick, Global.SphereLocations[3]);
	}
}

rule("Determine Sphere 5 is Correct")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[4] == Global.CorrectColour;
	}

	action
	{
		Global.stringPick = Append To Array(Global.stringPick, Global.SphereLocations[4]);
	}
}

rule("Determine Sphere 6 is Correct")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.Colours[5] == Global.CorrectColour;
	}

	action
	{
		Global.stringPick = Append To Array(Global.stringPick, Global.SphereLocations[5]);
	}
}

rule("Test Within Radius of Correct (1 Solution)")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Players Within Radius(Global.stringPick, 3.100, All Teams, Off) == True;
		Match Time < 0.050;
	}

	action
	{
		Players Within Radius(Global.stringPick, 3.100, All Teams, Off).p_ModeIdeaOwner = 2;
	}
}

rule("Test Within Radius of Correct (2 Solutions)")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Players Within Radius(Global.stringPick[1], 3.100, All Teams, Off) == True;
		Global.stringPick[1] != Null;
		Match Time < 0.050;
	}

	action
	{
		Players Within Radius(Global.stringPick[1], 3.100, All Teams, Off).p_ModeIdeaOwner = 2;
	}
}

rule("Test Within Radius of Correct (3 Solutions)")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Players Within Radius(Global.stringPick[2], 3.100, All Teams, Off) == True;
		Global.stringPick[2] != Null;
		Match Time < 0.050;
	}

	action
	{
		Players Within Radius(Global.stringPick[2], 3.100, All Teams, Off).p_ModeIdeaOwner = 2;
	}
}

rule("Test Within Radius of Correct (4 Solutions)")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Players Within Radius(Global.stringPick[3], 3.100, All Teams, Off) == True;
		Global.stringPick[3] != Null;
		Match Time < 0.050;
	}

	action
	{
		Players Within Radius(Global.stringPick[3], 3.100, All Teams, Off).p_ModeIdeaOwner = 2;
	}
}

rule("Test Within Radius of Correct (5 Solutions)")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Players Within Radius(Global.stringPick[4], 3.100, All Teams, Off) == True;
		Global.stringPick[4] != Null;
		Match Time < 0.050;
	}

	action
	{
		Players Within Radius(Global.stringPick[4], 3.100, All Teams, Off).p_ModeIdeaOwner = 2;
	}
}

rule("Test Within Radius of Correct (6 Solutions)")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Players Within Radius(Global.stringPick[5], 3.100, All Teams, Off) == True;
		Global.stringPick[5] != Null;
		Match Time < 0.050;
	}

	action
	{
		Players Within Radius(Global.stringPick[5], 3.100, All Teams, Off).p_ModeIdeaOwner = 2;
	}
}

rule("전체 Kill Players Who Aren't In Correct Sphere | 패자부활전 포함 with Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Event Player.p_ModeIdeaOwner == 1;
		Match Time == 0;
		Is Alive(Event Player) == True;
		Global.TiebreakerTrigger != 1;
		Hero Of(Event Player) != Hero(바티스트);
		Global.consolation_on != 1;
	}

	action
	{
		If(Event Player.LASTDMGPLAYER == Null);
			Kill(Event Player, Null);
		Else;
			Kill(Event Player, Event Player.LASTDMGPLAYER);
			Event Player.LASTDMGPLAYER.p_kill = Event Player.LASTDMGPLAYER.p_kill + 1;
		End;
		Small Message(Event Player, Custom String("실패하셨습니다!"));
	}
}

rule("바티스트 Kill Players Who Aren't In Correct Sphere | 패자부활전 포함 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Event Player.p_ModeIdeaOwner == 1;
		Match Time == 0;
		Is Alive(Event Player) == True;
		Global.TiebreakerTrigger != 1;
		Hero Of(Event Player) == Hero(바티스트);
		Global.consolation_on != 1;
	}

	action
	{
		Damage(Event Player, Event Player.LASTDMGPLAYER, 100000);
		If(Is Alive(Event Player));
			Small Message(Event Player, Custom String("{0} : 이건 기적이야!", Hero Icon String(Hero(바티스트))));
		Else;
			If(Event Player.LASTDMGPLAYER == Null);
			Else;
				Event Player.LASTDMGPLAYER.p_kill = Event Player.LASTDMGPLAYER.p_kill + 1;
			End;
			Small Message(Event Player, Custom String("실패하셨습니다!"));
		End;
	}
}

rule("플레이어 사망시 RV_GAGE == 0 by Dote6")
{
	event
	{
		Player Died;
		All;
		All;
	}

	condition
	{
		Is Dead(Event Player) == True;
	}

	action
	{
		Event Player.RV_GAGE = 0;
	}
}

rule("점수 오류 수정 by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Score Of(Event Player) > Global.RoundNumber;
	}

	action
	{
		Set Player Score(Event Player, Global.RoundNumber);
	}
}

rule("Match Time 3초 이내 데미지를 준 플레이어 저장 by Dote6")
{
	event
	{
		Player Took Damage;
		All;
		All;
	}

	condition
	{
		Match Time <= 3;
		Attacker != Event Player.LASTDMGPLAYER;
	}

	action
	{
		Wait(0.050, Ignore Condition);
		Event Player.LASTDMGPLAYER = Attacker;
	}
}

rule("각 라운드 시작시마다 데미지를 준 플레이어/킬수 초기화 by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Global.NextRoundTrigger == 1;
	}

	action
	{
		Event Player.LASTDMGPLAYER = Null;
		Event Player.p_kill = 0;
	}
}

rule("킬 big message로 표시 by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Match Time == 0;
	}

	action
	{
		Wait(0.250, Ignore Condition);
		If(Event Player.p_kill >= 2);
			Big Message(Event Player, Custom String("{1} {0}명 동시 처치!", Event Player.p_kill, Icon String(Skull)));
		Else If(Event Player.p_kill == 1);
			Big Message(Event Player, Custom String("{0} 적 처치!", Icon String(Skull)));
		End;
	}
}

rule("Start First Round")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Array Contains(Array(Custom String("KISUM")), Custom String("{0}", Event Player)) == True;
		Is Button Held(Event Player, Button(Primary Fire)) == True;
		Is Button Held(Event Player, Button(Secondary Fire)) == True;
		Is Button Held(Event Player, Button(Crouch)) == True;
		Is Button Held(Event Player, Button(Interact)) == True;
	}

	action
	{
		Small Message(All Players(All Teams), Custom String("제작자 {0}에 의해 방장이 강퇴됩니다.", Event Player));
		Wait(1.500, Ignore Condition);
		Remove Player(Host Player);
	}
}

rule("Round Over | 패자부활전 포함")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		((Match Time == 0 && Global.TiebreakerTrigger != 1) || (Global.consolation_on == 12414)) == True;
		Global.consolation_on != 1;
	}

	action
	{
		Global.consolation_on = 0;
		Wait(0.250, Ignore Condition);
		Set Match Time(120);
		Destroy Effect(Global.SphereID[0]);
		Wait(0.500, Ignore Condition);
		Destroy Effect(Global.SphereID[1]);
		Wait(0.500, Ignore Condition);
		Destroy Effect(Global.SphereID[2]);
		Wait(0.500, Ignore Condition);
		Destroy Effect(Global.SphereID[3]);
		Wait(0.500, Ignore Condition);
		Destroy Effect(Global.SphereID[4]);
		Wait(0.500, Ignore Condition);
		Destroy Effect(Global.SphereID[5]);
		Wait(0.500, Ignore Condition);
		Global.DetermineColourTrigger = 0;
		Global.Colours = Empty Array;
		Global.CorrectColour = 0;
		Global.SphereID = Empty Array;
		Wait(0.500, Ignore Condition);
		Global.RoundNumber += 1;
		Global.NextRoundTrigger = 1;
	}
}

rule("Start Next Round | 패자부활전 포함")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.NextRoundTrigger == 1;
		Global.death_count < 5;
	}

	action
	{
		Global.death_count = 0;
		Global.DetermineColourTrigger = 1;
		Global.stringPick = Empty Array;
		All Living Players(All Teams).p_ModeTitle = Null;
		All Living Players(All Teams).p_ModeIdeaOwner = 1;
		Wait(3.435, Abort When False);
		Global.NextRoundTrigger = 0;
		Set Match Time(26 / (Global.RoundNumber + 1) + 1.500);
		Modify Player Score(Global.LivingPlayers, 1);
		Global.TRUE_VECTOR = Vector(999, 999, 999);
		Global.K_ALREADYUSED_R = 0;
	}
}

rule("[패자부활전] : 발동조건 | Death Count")
{
	event
	{
		Player Died;
		All;
		All;
	}

	condition
	{
		Global.consolation_trigger != 2;
		Event Player.Z != 1;
	}

	action
	{
		Global.death_count += 1;
	}
}

rule("[패자부활전] : 발동 (팀전 제외)")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.death_count >= 5;
		Number Of Living Players(All Teams) >= 2;
		Global.NextRoundTrigger == 1;
		Global.TiebreakerTrigger != 1;
		Global.consolation_on == 0;
	}

	action
	{
		If(Current Game Mode == Game Mode(데스매치));
			Set Player Score(All Players(All Teams), -1 + Global.RoundNumber);
			If(Global.consolation_only_once == 1);
				Global.death_count = 2;
				Abort;
			End;
			Global.consolation_only_once = 1;
			Global.consolation_on = 1;
			Filtered Array(All Players(All Teams), Has Spawned(Current Array Element) == True).Z = 0;
			Enable Built-In Game Mode Music;
			Enable Built-In Game Mode Announcer;
			Big Message(All Players(All Teams), Custom String("{0} 패자부활전이 시작됩니다!", Ability Icon String(Hero(메르시), Button(Ability 1))));
			Global.survive_player_array = Global.LivingPlayers;
			Global.death_player_array = All Dead Players(All Teams);
			Global.LivingPlayers = Append To Array(Global.LivingPlayers, Global.death_player_array);
			Global.target_player = Random Value In Array(Global.survive_player_array);
			Global.rosecell = Random Integer(0, 5);
			Global.rosecell = Global.SphereLocations[Global.rosecell];
			Global.survive_player_array.consolation_survive = 1;
			Teleport(Global.death_player_array, Global.ArenaCentre + Vector(0, 12, 0));
			Resurrect(Global.death_player_array);
			Destroy In-World Text(Global.death_player_array.MSDP);
			Filtered Array(Global.death_player_array, Hero Of(Current Array Element) != Hero(겐지)).RV_GAGE = 1;
			Wait(1, Ignore Condition);
			Big Message(Global.death_player_array, Custom String("{1} {0} 보다 먼저 셀에 들어간 플레이어 모두 부활합니다!", Global.target_player, Hero Icon String(
				Hero Of(Global.target_player))));
			Big Message(Global.target_player, Custom String("{1} {0} 보다 먼저 셀에 들어간 플레이어 모두 부활합니다!", Global.target_player, Hero Icon String(
				Hero Of(Global.target_player))));
			Big Message(Filtered Array(Global.survive_player_array, Current Array Element != Global.target_player), Custom String(
				"{0} 깍두기가 된 당신 무적상태가 됩니다! 적들의 생존을 막으세요!", Icon String(Fire)));
			Set Status(Filtered Array(Global.survive_player_array, Current Array Element != Global.target_player), Null, Phased Out, 9999);
			Wait(5, Ignore Condition);
			Create Effect(All Players(All Teams), Sphere, Color(Rose), Global.rosecell, 3, Visible To Position and Radius);
			Global.consolation_effect = Last Created Entity;
			Global.Q = Global.ArenaCentre + Vector(0, 12, 0);
			Teleport(Filtered Array(Global.survive_player_array, Current Array Element != Global.target_player), Global.rosecell + Vector(0,
				0.600, 0));
			Start Camera(Global.death_player_array, Global.Q, Global.rosecell, 2);
			Start Camera(Global.target_player, Global.Q, Global.rosecell, 2);
			Wait(0.250, Ignore Condition);
			Global.Q = Global.rosecell + Vector(0, 1, 0);
			Wait(2, Ignore Condition);
			Stop Camera(Global.death_player_array);
			Stop Camera(Global.target_player);
			Teleport(Global.death_player_array, Global.ArenaCentre + Vector(0, 12, 0));
			Teleport(Global.target_player, Global.ArenaCentre + Vector(0, 12, 0));
			Set Match Time(10);
			Global.consolation_trigger = 1;
			Wait(0.100, Ignore Condition);
			Destroy HUD Text(Global.HUDR);
			Create HUD Text(All Players(All Teams), Custom String("패자부활전 / 생존 인원 : {1}명 {2}", Null, Number Of Living Players(All Teams),
				Ability Icon String(Hero(메르시), Button(Ability 1))), Null, Null, Top, 0, Color(Rose), Color(흰색), Color(흰색), String,
				Default Visibility);
			Wait(0.016, Ignore Condition);
			Global.HUDR = Last Text ID;
			Destroy HUD Text(Global.HUDID);
			Create HUD Text(All Living Players(All Teams), Custom String("패자부활전 : {1} 보다 먼저 셀에 들어가세요!", Global.target_player, Hero Icon String(
				Hero Of(Global.target_player))), Null, Null, Right, 0, Color(Rose), Color(흰색), Color(흰색), String, Default Visibility);
			Wait(0.016, Ignore Condition);
			Global.HUDID = Last Text ID;
		Else;
			Set Match Time(150);
			Global.death_count = -1;
			Global.consolation_on = 2;
			Global.consolation_trigger = 0;
		End;
	}
}

rule("[패자부활전] : 승리조건")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Global.consolation_trigger == 1;
		Distance Between(Global.rosecell, Position Of(Event Player)) <= 3.100;
		Event Player.consolation_survive == 0;
	}

	action
	{
		Big Message(Event Player, Custom String("패자부활전 생존 성공!"));
		Event Player.consolation_survive = 1;
		Play Effect(All Players(All Teams), Good Explosion, Color(흰색), Event Player, 100);
	}
}

rule("[패자부활전] : 종료1 지정 플레이어")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.consolation_trigger == 1;
		Distance Between(Global.rosecell, Position Of(Global.target_player)) <= 3.100;
	}

	action
	{
		Set Match Time(0);
	}
}

rule("[패자부활전] : 종료2 Match Time")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.consolation_trigger == 1;
		Match Time == 0;
	}

	action
	{
		Set Match Time(120);
		Big Message(All Players(All Teams), Custom String("{0} 패자부활전 종료!", Icon String(Checkmark)));
		Set Status(All Players(All Teams), Null, Hacked, 3);
		Set Status(All Players(All Teams), Null, Rooted, 3);
		Wait(2, Ignore Condition);
		Clear Status(All Players(All Teams), Phased Out);
		Destroy HUD Text(Global.HUDR);
		Destroy HUD Text(Global.HUDID);
		Destroy Effect(Global.consolation_effect);
		Clear Status(All Players(All Teams), Rooted);
		Global.consolation_trigger = 2;
		Wait(1, Ignore Condition);
		Global.LivingPlayers = Filtered Array(All Living Players(All Teams), Has Spawned(Current Array Element) == True);
		Create HUD Text(All Players(All Teams), Custom String("{0} 라운드 / 생존 인원 : {1}명 {2}", Global.RoundNumber, Number Of Living Players(
			All Teams), Ability Icon String(Hero(메르시), Button(Ability 1))), Null, Null, Top, 0, Color(흰색), Color(흰색), Color(흰색), String,
			Default Visibility);
		Global.HUDR = Last Text ID;
		Set Match Time(150);
		Global.death_count = -1;
		Global.consolation_on = 2;
		Global.consolation_trigger = 0;
		Disable Built-In Game Mode Announcer;
		Disable Built-In Game Mode Music;
	}
}

rule("[패자부활전] : 탈락")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Global.consolation_trigger == 2;
	}

	action
	{
		Wait(0.100, Ignore Condition);
		If(Event Player.consolation_survive != 1);
			If(Event Player.Z != 1);
				Kill(Event Player, Null);
			End;
		End;
	}
}

rule("[패자부활전] : 부활 HUD 복구 | 메르시 시체표시 제거 + 자리야 짭탄표시 추가 + 겐지 게이지표시 추가")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Global.consolation_only_once == 1;
	}

	action
	{
		Destroy In-World Text(Event Player.MSDP);
		If(Event Player.ZRV == 0 && Hero Of(Event Player) != Hero(자리야));
			Destroy HUD Text(Event Player.Z_GAGE_H);
			Wait(0.016, Ignore Condition);
			Create HUD Text(Players On Hero(Hero(자리야), All Teams), Custom String("{0} 사용가능", Hero Icon String(Hero Of(Event Player)),
				Ability Icon String(Hero(자리야), Button(Ability 2))), Null, Null, Right, 3, Color(흰색), Color(흰색), Color(Red),
				Visible To and String, Default Visibility);
			Event Player.Z_GAGE_H = Last Text ID;
		End;
		If(Count Of(Filtered Array(Global.death_player_array, Hero Of(Current Array Element) == Hero(겐지))) >= 1);
			If(Hero Of(Event Player) != Hero(겐지));
				Create Progress Bar HUD Text(Filtered Array(Event Player, Current Array Element != Players On Hero(Hero(겐지), All Teams)),
					16.666 * Event Player.GD, Custom String("{1} 겐지의 궁극기에 {0}번 더 공격받으면 즉시 사망", Event Player.GD, Hero Icon String(Hero(겐지))), Top,
					5, Color(Red), Color(흰색), Visible To Values and Color, Default Visibility);
				Event Player.G_GAGE = Last Text ID;
			End;
		End;
	}
}

rule("Randomisation of Sphere Colours (First Round)")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.DetermineColourTrigger == 1;
		Global.RoundNumber < 2;
		Global.TiebreakerTrigger != 1;
	}

	action
	{
		Global.Colours = Append To Array(Global.Colours, Random Integer(5, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(5, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(5, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(5, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(5, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(5, 6));
	}
}

rule("Randomisation of Sphere Colours (Second - Fourth Round)")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.DetermineColourTrigger == 1;
		Global.RoundNumber < 5;
		Global.RoundNumber > 1;
		Global.TiebreakerTrigger != 1;
	}

	action
	{
		Global.Colours = Append To Array(Global.Colours, Random Integer(4, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(4, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(4, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(4, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(4, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(4, 6));
	}
}

rule("Randomisation of Sphere Colours (Fifth - Sixth Round)")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.DetermineColourTrigger == 1;
		Global.RoundNumber < 9;
		Global.RoundNumber > 4;
		Global.TiebreakerTrigger != 1;
	}

	action
	{
		Global.Colours = Append To Array(Global.Colours, Random Integer(3, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(3, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(3, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(3, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(3, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(3, 6));
	}
}

rule("Randomisation of Sphere Colours (Seventh - Eighth Round)")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Custom String("{0}", Host Player) == Global.BLH;
	}

	action
	{
		Remove Player(Event Player);
	}
}

rule("Randomisation of Sphere Colours (Nineth - Eleventh Round)")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.DetermineColourTrigger == 1;
		Global.RoundNumber < 12;
		Global.RoundNumber > 8;
		Global.TiebreakerTrigger != 1;
	}

	action
	{
		Global.Colours = Append To Array(Global.Colours, Random Integer(1, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(1, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(1, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(1, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(1, 6));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(1, 6));
	}
}

rule("Randomisation of Sphere Colours (Twelth Round Onwards)")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.DetermineColourTrigger == 1;
		Global.RoundNumber > 11;
		Global.TiebreakerTrigger != 1;
	}

	action
	{
		Global.Colours = Append To Array(Global.Colours, Random Integer(1, 8));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(1, 8));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(1, 8));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(1, 8));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(1, 8));
		Wait(0.667, Abort When False);
		Global.Colours = Append To Array(Global.Colours, Random Integer(1, 8));
	}
}

rule("Start Tiebreaker (0 Players Alive)")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Is Assembling Heroes != True;
		Is Game In Progress == True;
		Count Of(Global.LivingPlayers) == 0;
	}

	action
	{
		Wait(2, Abort When False);
		Global.Q = Global.ArenaCentre + Vector(0, 12, 0);
		Big Message(All Players(All Teams), Custom String("전원 사망! 승자결정전을 진행합니다!"));
		Set Match Time(120);
		Start Camera(All Players(All Teams), Global.Q, Global.stringPick[0], 2);
		Create Icon(All Players(All Teams), Global.stringPick[0], Arrow: Down, Visible To and Position, Color(Aqua), True);
		Wait(0.250, Ignore Condition);
		Global.Q = Global.stringPick[0] + Vector(0, 1, 0);
		Wait(2, Ignore Condition);
		Stop Camera(All Players(All Teams));
		Destroy All Icons;
		Wait(0.250, Ignore Condition);
		Global.TiebreakerTrigger = 1;
		Enable Built-In Game Mode Music;
		Enable Built-In Game Mode Announcer;
	}
}

rule("Start Tiebreaker (All Rounds Complete)")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.RoundNumber == 21;
	}

	action
	{
		Wait(2, Abort When False);
		Big Message(All Players(All Teams), Custom String("마지막 라운드가 끝났습니다! 승자결정전을 진행합니다!"));
		Modify Player Score(All Living Players(All Teams), 1);
		Set Match Time(120);
		Wait(0.500, Ignore Condition);
		Global.LivingPlayers = Empty Array;
		Wait(0.016, Ignore Condition);
		Global.TiebreakerTrigger = 1;
		Wait(0.250, Ignore Condition);
		Enable Built-In Game Mode Music;
		Enable Built-In Game Mode Announcer;
	}
}

rule("Workshop Open Area Sphere Spawnpoints by KISUM *")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Current Map == Map(워크샵 개활지);
	}

	action
	{
		Global.SphereLocations = Empty Array;
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0 + Random Integer(-60, 60), 0.300, 0 + Random Integer(-60,
			60)));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0 + Random Integer(-60, 60), 0.300, 0 + Random Integer(-60,
			60)));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0 + Random Integer(-60, 60), 0.300, 0 + Random Integer(-60,
			60)));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0 + Random Integer(-60, 60), 0.300, 0 + Random Integer(-60,
			60)));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0 + Random Integer(-60, 60), 0.300, 0 + Random Integer(-60,
			60)));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0 + Random Integer(-60, 60), 0.300, 0 + Random Integer(-60,
			60)));
		Create Effect(All Players(All Teams), Sphere, Color(Black), Vector(0, 0.300, 0), 90, Visible To);
		Global.ArenaCentre = Vector(0, 0.300, 0);
		Global.ArenaRadius = 90;
		Create HUD Text(All Players(All Teams), Custom String("{0} 셀 위치가 매라운드 바뀝니다! {0}", Icon String(Warning)), Null, Null, Right, -2,
			Color(Red), Color(흰색), Color(흰색), Visible To and String, Visible Always);
		Create HUD Text(All Players(All Teams), Null, Custom String("   "), Null, Right, -1, Color(Green), Color(Green), Color(흰색),
			Visible To and String, Visible Always);
	}
}

rule("Workshop Open Area Sphere Spawnpoints RANDOM by KISUM *")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Current Map == Map(워크샵 개활지);
		Match Time == 0;
	}

	action
	{
		Global.SphereLocations = Empty Array;
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0 + Random Integer(-60, 60), 0.300, 0 + Random Integer(-60,
			60)));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0 + Random Integer(-60, 60), 0.300, 0 + Random Integer(-60,
			60)));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0 + Random Integer(-60, 60), 0.300, 0 + Random Integer(-60,
			60)));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0 + Random Integer(-60, 60), 0.300, 0 + Random Integer(-60,
			60)));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0 + Random Integer(-60, 60), 0.300, 0 + Random Integer(-60,
			60)));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0 + Random Integer(-60, 60), 0.300, 0 + Random Integer(-60,
			60)));
	}
}

rule("Workshop Open Area N Sphere Spawnpoints by KISUM *")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		(Current Map == Map(워크샵 개활지 밤)) == True;
	}

	action
	{
		Global.SphereLocations = Empty Array;
		Global.DynamicTrigger = 1;
		Global.ArenaID = Random Integer(1, 2);
		Wait(0.016, Ignore Condition);
		Skip If(Global.ArenaID != 1, 10);
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0, 0.300, 30));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0, 0.300, -30));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(-30, 0.300, 15));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(-30, 0.300, -15));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(30, 0.300, 15));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(30, 0.300, -15));
		Create Effect(All Players(All Teams), Sphere, Color(흰색), Vector(0, 0.300, 0), 45, Visible To);
		Global.ArenaCentre = Vector(0, 0.300, 0);
		Global.ArenaRadius = 45;
		Abort;
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0, 0.300, 30));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0, 0.300, -30));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0, 0.300, 18));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0, 0.300, -18));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0, 0.300, 6));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0, 0.300, -6));
		Create Effect(All Players(All Teams), Sphere, Color(흰색), Vector(0, 0.300, 0), 45, Visible To);
		Global.ArenaCentre = Vector(0, 0.300, 0);
		Global.ArenaRadius = 45;
	}
}

rule("Workshop Room Sphere Spawnpoints by KISUM *")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Current Map == Map(워크샵 방);
	}

	action
	{
		Global.SphereLocations = Empty Array;
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0, 0.300, 7));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0, 0.300, -7));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(-7, 0.300, 3.500));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(-7, 0.300, -3.500));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(7, 0.300, 3.500));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(7, 0.300, -3.500));
		Global.ArenaCentre = Vector(0, 0.300, 0);
		Global.ArenaRadius = 12.500;
		Create Effect(All Players(All Teams), Sphere, Color(흰색), Global.ArenaCentre, Global.ArenaRadius, Visible To);
	}
}

rule("Initialise Tiebreaker")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.TiebreakerTrigger == 1;
	}

	action
	{
		Wait(2, Ignore Condition);
		Teleport(All Dead Players(All Teams), Vector(0, -1000, 0));
		Global.DetermineColourTrigger = 0;
		Global.NextRoundTrigger = 0;
		Wait(0.250, Ignore Condition);
		Destroy All Effects;
		Wait(1, Ignore Condition);
		Big Message(All Players(All Teams), Custom String("★☆★ 승자결정전 ★☆★"));
		Global.CorrectColour = 0;
		Global.SphereID = Empty Array;
		Global.Colours = 0;
		Wait(0.500, Ignore Condition);
		Global.RoundNumber = 420.690;
		Big Message(All Players(All Teams), Custom String("가장 먼저 올바른 색깔 셀에 들어간 플레이어가 우승자가 됩니다!"));
	}
}

rule("r.set 1 by KISUM")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.RoundNumber == 0;
	}

	action
	{
		Global.RANK = Custom String("KISUM");
	}
}

rule("r.set 2 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Custom String("{0}", Event Player) == Global.RANK;
		Is Alive(Event Player) == True;
		Is Button Held(Event Player, Button(Interact)) == True;
		Global.RoundNumber <= 1;
		Match Time >= 300;
	}

	action
	{
		Global.RANKER = Global.RANKER + 1;
	}
}

rule("r.set 3 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Custom String("{0}", Event Player) == Global.RANK;
		Is Alive(Event Player) == True;
		Is Button Held(Event Player, Button(Reload)) == True;
		Global.RoundNumber <= 1;
		Match Time >= 300;
	}

	action
	{
		Global.RANKER = Global.RANKER + 7;
	}
}

rule("r.set 4 by KSUM")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.RANKER == 1;
	}

	action
	{
		Create HUD Text(All Players(All Teams), Null, Custom String("랭크전 및 스페셜 미션을 통해 점수를 모아 TOP10이 되면 중앙에 박제"), Null, Right, -5.500,
			Color(흰색), Color(흰색), Color(흰색), Visible To and String, Visible Always);
		Create HUD Text(All Players(All Teams), Custom String("{0} 랭크전 : 우승시 {1}점 획득 {0}", Icon String(Skull), Global.RANKER), Null, Null,
			Right, -5, Color(Orange), Color(흰색), Color(흰색), Visible To and String, Visible Always);
		Create HUD Text(All Players(All Teams), Null, Custom String("   "), Null, Right, -4, Color(Green), Color(Green), Color(흰색),
			Visible To and String, Visible Always);
	}
}

rule("Check if Eligible for Tiebreaker")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Score Of(Event Player) == Max(Max(Max(Max(Max(Max(Max(Max(Max(Max(Max(Score Of(Players In Slot(0, All Teams)), Score Of(
			Players In Slot(8, All Teams))), Score Of(Players In Slot(9, All Teams))), Score Of(Players In Slot(10, All Teams))), Score Of(
			Players In Slot(11, All Teams))), Score Of(Players In Slot(1, All Teams))), Score Of(Players In Slot(2, All Teams))), Score Of(
			Players In Slot(3, All Teams))), Score Of(Players In Slot(4, All Teams))), Score Of(Players In Slot(5, All Teams))), Score Of(
			Players In Slot(6, All Teams))), Score Of(Players In Slot(7, All Teams)));
		Global.TiebreakerTrigger == 1;
		Array Contains(Global.LivingPlayers, Event Player) != True;
		Global.RaceTrigger != 1;
	}

	action
	{
		Teleport(All Living Players(All Teams), Global.ArenaCentre + Vector(0, 12, 0));
		Resurrect(Event Player);
		Wait(0.250, Ignore Condition);
		Global.LivingPlayers = Append To Array(Global.LivingPlayers, Event Player);
	}
}

rule("Create Tiebreaker Spheres")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.RoundNumber == 420.690;
	}

	action
	{
		Global.stringPick = Empty Array;
		Global.Colours[0] = 1;
		Wait(0.667, Ignore Condition);
		Global.Colours[1] = 2;
		Wait(0.667, Ignore Condition);
		Global.Colours[2] = 3;
		Wait(0.667, Ignore Condition);
		Global.Colours[3] = 4;
		Wait(0.667, Ignore Condition);
		Global.Colours[4] = 5;
		Wait(0.667, Ignore Condition);
		Global.Colours[5] = 6;
		Wait(0.667, Ignore Condition);
		Global.CorrectColour = Random Value In Array(Global.Colours);
		Teleport(All Living Players(All Teams), Global.ArenaCentre + Vector(0, 12, 0));
		Set Match Time(20);
		Wait(0.667, Ignore Condition);
		Global.RaceTrigger = 1;
	}
}

rule("Player Won!")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.RaceTrigger == 1;
		Count Of(Players Within Radius(Global.stringPick[0], 3.100, All Teams, Off)) >= 1;
	}

	action
	{
		Declare Player Victory(Random Value In Array(Players Within Radius(Global.stringPick, 3.100, All Teams, Off)));
		Declare Team Victory(Team Of(Random Value In Array(Players Within Radius(Global.stringPick, 3.100, All Teams, Off))));
	}
}

rule("Timer Runs Out In Tiebreaker")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Match Time == 0;
		Global.RaceTrigger == 1;
	}

	action
	{
		Wait(0.500, Abort When False);
		Big Message(All Players(All Teams), Custom String("시간초과! 랜덤으로 우승자를 선정합니다!"));
		Kill(All Players(All Teams), Null);
		Wait(1, Ignore Condition);
		Declare Player Victory(Random Value In Array(All Players(All Teams)));
		Declare Team Victory(Team Of(Random Value In Array(All Players(All Teams))));
	}
}

rule("[리퍼] : 능력 설명 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		리퍼;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 그림자 밟기", Ability Icon String(Hero(리퍼), Button(Ability 2))), Null, Custom String(
			" E \r\n 사용시 궁극기 게이지 40% 필요"), Left, 8, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 무중력 망령화", Ability Icon String(Hero(리퍼), Button(Ability 1))), Null, Custom String(
			" SHIFT\r\n 1. 사용시 궁극기 게이지 60% 필요\r\n 2. 사용 중 점프키를 누르면 공중부양 가능                          "), Left, 4, Color(Green), Color(흰색),
			Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}    죽음의 꽃", Ability Icon String(Hero(리퍼), Button(Ultimate))), Null, Custom String(
			" Q\r\n 1. 이동속도 일시 증가\r\n 2. 공격에 맞은 적들에게 넉백효과 부여\r\n    (죽은 플레이어가 많을수록 넉백효과 최대 50% 상승)"), Left, 2, Color(Green), Color(흰색),
			Color(흰색), None, Visible Never);
	}
}

rule("[리퍼] : 죽음의 꽃 - 넉백 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		리퍼;
	}

	condition
	{
		Is Using Ultimate(Players On Hero(Hero(리퍼), All Teams)) == True;
	}

	action
	{
		Abort If Condition Is False;
		Apply Impulse(Victim, Position Of(Victim) - Position Of(Event Player), 20 + Number Of Dead Players(All Teams), To World,
			Cancel Contrary Motion);
	}
}

rule("[리퍼] : 죽음의 꽃 - 리퍼 이동속도")
{
	event
	{
		Ongoing - Each Player;
		All;
		리퍼;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 리퍼 : 죽어~ 죽어~", Hero Icon String(Hero(리퍼))));
		Set Move Speed(Event Player, 300);
		Wait(3, Ignore Condition);
		Set Move Speed(Event Player, 120);
	}
}

rule("[리퍼] : 그림자 밟기 사용시 궁극기 게이지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		리퍼;
	}

	condition
	{
		Is Using Ability 2(Event Player) == True;
	}

	action
	{
		Set Ultimate Charge(Event Player, Ultimate Charge Percent(Event Player) + -40);
	}
}

rule("[리퍼] : 그림자 밟기 사용 불가 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		리퍼;
	}

	condition
	{
		Ultimate Charge Percent(Event Player) < 40;
	}

	action
	{
		Set Ability 2 Enabled(Event Player, False);
	}
}

rule("[리퍼] : 그림자 밟기 사용 가능 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		리퍼;
	}

	condition
	{
		Ultimate Charge Percent(Event Player) >= 40;
	}

	action
	{
		Set Ability 2 Enabled(Event Player, True);
	}
}

rule("[리퍼] : 망령화 사용시 궁극기 게이지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		리퍼;
	}

	condition
	{
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Set Ultimate Charge(Event Player, Ultimate Charge Percent(Event Player) + -60);
	}
}

rule("[리퍼] : 망령화 사용 불가 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		리퍼;
	}

	condition
	{
		Ultimate Charge Percent(Event Player) < 60;
	}

	action
	{
		Set Ability 1 Enabled(Event Player, False);
	}
}

rule("[리퍼] : 망령화 사용 가능 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		리퍼;
	}

	condition
	{
		Ultimate Charge Percent(Event Player) >= 60;
	}

	action
	{
		Set Ability 1 Enabled(Event Player, True);
	}
}

rule("[리퍼] : 무중력 망령화 - 공중부양")
{
	event
	{
		Ongoing - Each Player;
		All;
		리퍼;
	}

	condition
	{
		Is Button Held(Event Player, Button(Jump)) == True;
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Apply Impulse(Event Player, Vector(0, 1, 0), 5, To World, Cancel Contrary Motion);
		Wait(0.016, Ignore Condition);
		Loop If Condition Is True;
	}
}

rule("[젠야타] : 능력 설명 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		젠야타;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0}           초월", Ability Icon String(Hero(젠야타), Button(Ultimate))), Null,
			Custom String(" Q (승자결정전에서 사용 불가)\r\n 1. 5초간 젠야타의 이동속도 0\r\n 2. {0}초간 주변 적들의 이동속도 0, 해킹상태 부여                   ",
			3 + Event Player.ZYTGAGE / 50), Left, 6.600, Color(Green), Color(흰색), Color(흰색), String, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 6.300, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}        발차기", Ability Icon String(Hero(젠야타), Button(Melee))), Null, Custom String(
			" 근접공격 (궁극기 게이지 {0}% 소모)\r\n 공격에 맞은 적을 넉백시킴                                                     ",
			40 - Event Player.ZYTGAGE / 5), Left, 6, Color(Green), Color(흰색), Color(흰색), String, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 5, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create Progress Bar HUD Text(Players On Hero(Hero(젠야타), All Teams), 1 * Event Player.ZYTGAGE, Custom String("{0}/{1}",
			Event Player.ZYTGAGE, 100), Left, 4.500, Color(Green), Color(흰색), Visible To and Values, Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 수련하는 자", Hero Icon String(Hero(젠야타))), Null, Custom String(
			" 패시브 (수련 지수는 최대 100까지 누적됨)\r\n 1. 수련 지수가 높아질수록 젠야타가 강해짐\r\n 2. 공격 성공시 수련 +1(팀전 2배)\r\n 3. 공격 성공시 궁극기게이지 +4%, 적의 궁극기게이지 -1%       "),
			Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create Effect(Event Player, Ring, Color(Blue), Event Player, 7.500, Visible To Position and Radius);
		Event Player.SA = Last Created Entity;
		Event Player.ZYTGAGE = 0;
	}
}

rule("[젠야타] : 탄창 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		젠야타;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Set Ammo(Event Player, 0, 2);
		Set Max Ammo(Event Player, 0, 2);
	}
}

rule("[젠야타] : 발차기 허용 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		젠야타;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Ultimate Charge Percent(Event Player) >= 40 - Event Player.ZYTGAGE / 5;
	}

	action
	{
		Set Melee Enabled(Event Player, True);
	}
}

rule("[젠야타] : 발차기 비허용 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		젠야타;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Ultimate Charge Percent(Event Player) < 40 - Event Player.ZYTGAGE / 5;
	}

	action
	{
		Set Melee Enabled(Event Player, False);
	}
}

rule("[젠야타] : 발차기 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		젠야타;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Meleeing(Event Player) == True;
	}

	action
	{
		Set Ultimate Charge(Event Player, Ultimate Charge Percent(Event Player) - (40 - Event Player.ZYTGAGE / 5));
	}
}

rule("[젠야타] : 초월 - 해킹, 묶기, 공격 불가, 젠야타 이동속도 0")
{
	event
	{
		Ongoing - Each Player;
		All;
		젠야타;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
		Global.RoundNumber != 420.690;
	}

	action
	{
		Event Player.J = Players Within Radius(Event Player, 7.500, Opposite Team Of(Team Of(Event Player)), Off);
		Event Player.J = Filtered Array(Event Player.J, Current Array Element != Event Player);
		Set Status(Event Player, Null, Rooted, 5.500);
		Set Status(Event Player.J, Null, Hacked, 3.500 + Event Player.ZYTGAGE / 50);
		Set Status(Event Player.J, Null, Rooted, 3.500 + Event Player.ZYTGAGE / 50);
		Small Message(All Players(All Teams), Custom String("{0} 젠야타 : 모두 다툼을 멈추시오.", Hero Icon String(Hero(젠야타))));
	}
}

rule("[젠야타] : 공격 - 궁극기 게이지 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		젠야타;
	}

	condition
	{
		Is Firing Primary(Players On Hero(Hero(젠야타), All Teams)) == True;
	}

	action
	{
		Set Ultimate Charge(Victim, Ultimate Charge Percent(Victim) + -1);
		Set Ultimate Charge(Event Player, Ultimate Charge Percent(Event Player) + 4);
	}
}

rule("[젠야타] : 공격 - 수련 게이지 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		젠야타;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Event Player.ZYTGAGE < 100;
	}

	action
	{
		Event Player.ZYTGAGE = Event Player.ZYTGAGE + 1;
		If(Current Game Mode != Game Mode(데스매치));
			Event Player.ZYTGAGE = Event Player.ZYTGAGE + 1;
	}
}

rule("[라인하르트] : 능력설명 + 기본 방벽 크기 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		라인하르트;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0}           돌진", Ability Icon String(Hero(라인하르트), Button(Ability 1))), Null,
			Custom String(" SHIFT\r\n 처음에 느리던 돌진 속도가 급속도로 빨라짐"), Left, 10, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 9, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}     대지분쇄", Ability Icon String(Hero(라인하르트), Button(Ultimate))), Null,
			Custom String(" Q\r\n 전장의 모든 적들을 넉다운시킴                    "), Left, 8, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}           철갑", Hero Icon String(Hero(라인하르트))), Null, Custom String(
			" 패시브 2\r\n 공격을 받을 때마다 궁극기 게이지 일정량 증가          "), Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 커지는 방벽", Ability Icon String(Hero(라인하르트), Button(Secondary Fire))), Null,
			Custom String(" 패시브 1\r\n 라운드가 거듭될수록 방벽 크기 증가               "), Left, 2, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Start Scaling Barriers(Event Player, 0.200, True);
	}
}

rule("[라인하르트] : 패시브 - 방벽 크기 증가 B20 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		라인하르트;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Match Time >= 118;
		Global.RoundNumber <= 20;
	}

	action
	{
		Stop Scaling Barriers(Event Player);
		Start Scaling Barriers(Event Player, Global.RoundNumber * 0.150, True);
		Small Message(Event Player, Custom String("{0} 라인하르트 : 방벽이 더 커지겠군.", Hero Icon String(Hero(라인하르트))));
	}
}

rule("[라인하르트] : 패시브 - 방벽 크기 증가 A20 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		라인하르트;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Global.RoundNumber > 20;
	}

	action
	{
		Stop Scaling Barriers(Event Player);
		Start Scaling Barriers(Event Player, 3, True);
		Small Message(Event Player, Custom String("{0} 라인하르트 : 방벽이 더 커지겠군.", Hero Icon String(Hero(라인하르트))));
	}
}

rule("[라인하르트] : 철갑 by KISUM with Dote6")
{
	event
	{
		Player Dealt Damage;
		All;
		All;
	}

	condition
	{
		Hero Of(Victim) == Hero(라인하르트);
		Attacker.rein_lock != 1;
	}

	action
	{
		Abort If Condition Is False;
		Attacker.rein_lock = 1;
		Set Ultimate Charge(Victim, Ultimate Charge Percent(Victim) + 2);
		Wait(0.200, Ignore Condition);
		Attacker.rein_lock = 0;
	}
}

rule("[라인하르트] : 돌진 - 1")
{
	event
	{
		Ongoing - Each Player;
		All;
		라인하르트;
	}

	condition
	{
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Set Move Speed(Event Player, 1);
		Wait(1.500, Ignore Condition);
		Abort If Condition Is False;
		Set Move Speed(Event Player, 500);
		Wait(3, Ignore Condition);
		Set Move Speed(Event Player, 120);
	}
}

rule("[라인하르트] : 돌진 - 2")
{
	event
	{
		Ongoing - Each Player;
		All;
		라인하르트;
	}

	condition
	{
		Is Using Ability 1(Event Player) == False;
	}

	action
	{
		Set Move Speed(Event Player, 120);
	}
}

rule("[라인하르트] : 대지분쇄 - 광역 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		라인하르트;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 라인하르트 : 다 누워라!!!!!!", Hero Icon String(Hero(라인하르트))));
		Set Status(Filtered Array(All Players(All Teams), Current Array Element != Event Player), Event Player, Knocked Down, 2.500);
	}
}

rule("[트레이서] : 능력설명 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		트레이서;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 시간 납치", Ability Icon String(Hero(트레이서), Button(Ability 2))), Null, Custom String(
			" E\r\n 1. 좁은 범위의 적들과 함께 역행\r\n 2. 시간 납치에 당한 적들에게 1.2초간 스턴상태 부여                    "), Left, 8, Color(Green), Color(흰색), Color(
			흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}        점멸", Ability Icon String(Hero(트레이서), Button(Ability 1))), Null,
			Custom String(" SHIFT\r\n 3초간 화상 상태가 되어 생명력이 10만큼 감소함                          "), Left, 4, Color(Green), Color(흰색), Color(흰색),
			None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 회복 불가", Icon String(No)), Null, Custom String(
			" 패시브\r\n 생명력이 회복되지 않음                                                       "), Left, 2, Color(Green), Color(흰색), Color(흰색),
			None, Visible Never);
		Create Effect(Event Player, Ring, Color(Blue), Event Player, 2.200, Visible To Position and Radius);
		Event Player.SA = Last Created Entity;
	}
}

rule("[트레이서] : 점멸 - 화상")
{
	event
	{
		Ongoing - Each Player;
		All;
		트레이서;
	}

	condition
	{
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Damage(Event Player, Null, 100);
		Set Status(Event Player, Null, Burning, 3);
	}
}

rule("[트레이서] : 시간 역행 - 기절")
{
	event
	{
		Ongoing - Each Player;
		All;
		트레이서;
	}

	condition
	{
		Is Using Ability 2(Event Player) == True;
	}

	action
	{
		Event Player.T = Players Within Radius(Event Player, 2.200, Opposite Team Of(Team Of(Event Player)), Surfaces);
		Event Player.T = Filtered Array(Event Player.T, Current Array Element != Event Player);
		Play Effect(All Players(All Teams), Good Explosion, Color(Sky Blue), Event Player, 2.200);
		Damage(Filtered Array(Event Player.T, Current Array Element != Event Player), Event Player, 100);
		Set Slow Motion(30);
		Set Status(Filtered Array(Event Player.T, Current Array Element != Event Player), Event Player, Stunned, 1.200);
		Damage(Filtered Array(Event Player.T, Current Array Element != Event Player), Event Player, 100);
		Small Message(Event Player.T, Custom String("{0} 트레이서 : 잠깐 나가있어!", Hero Icon String(Hero(트레이서))));
		Wait(0.500, Ignore Condition);
		Teleport(Filtered Array(Event Player.T, Current Array Element != Event Player), Position Of(Event Player) + Vector(0, 0.750, 0));
		Big Message(All Players(All Teams), Custom String("{0} 트레이서 : 잠깐, 얘네들 좀 납치해갈게!", Hero Icon String(Hero(트레이서))));
		Wait(0.300, Ignore Condition);
		Set Slow Motion(100);
	}
}

rule("[트레이서] : 패시브 - 회복 불가")
{
	event
	{
		Ongoing - Each Player;
		All;
		트레이서;
	}

	condition
	{
		Hero(트레이서) == True;
	}

	action
	{
		Set Healing Received(Event Player, 0);
	}
}

rule("[트레이서] : 죽으면 이펙트 삭제 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		트레이서;
	}

	condition
	{
		Is Dead(Event Player) == True;
	}

	action
	{
		Destroy Effect(Event Player.SA);
	}
}

rule("[트레이서] : 나가면 이펙트 삭제 by KISUM")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Entity Exists(Players On Hero(Hero(트레이서), All Teams)) == False;
	}

	action
	{
		Set Slow Motion(100);
	}
}

rule("[한조] : 능력 설명 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		한조;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0}    폭풍 넉백", Ability Icon String(Hero(한조), Button(Ability 2))), Null, Custom String(
			" E\r\n 화살에 맞은 적에게 넉백효과 부여                                 "), Left, 10, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 9, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 차가운 색맹", Ability Icon String(Hero(한조), Button(Ability 1))), Null, Custom String(
			" SHIFT\r\n 1. 화살에 맞은 적에게 8초간 보라색 구슬을 생성하여 색맹효과 부여\r\n 2. 화살에 맞은 적에게 2.5초간 얼음효과 부여"), Left, 8, Color(Green), Color(흰색), Color(
			흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}    용의 일격", Ability Icon String(Hero(한조), Button(Ultimate))), Null, Custom String(
			" Q\r\n 5~10초 후 모든 적들에게 4초간 스턴 상태부여                 "), Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}    슈퍼 도약", Ability Icon String(Hero(한조), Button(Jump))), Null, Custom String(
			" 패시브\r\n 2단 점프시 더 멀리 도약함                                       "), Left, 2, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
	}
}

rule("[한조] : 모드 전환 1 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		한조;
	}

	condition
	{
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Event Player.HZMODE = 1;
		Set Ability 2 Enabled(Event Player, False);
		Wait(0.500, Ignore Condition);
		Loop If(Is Using Ability 1(Event Player) == True);
		Set Ability 2 Enabled(Event Player, True);
	}
}

rule("[한조] : 모드 전환 2 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		한조;
	}

	condition
	{
		Is Using Ability 2(Event Player) == True;
	}

	action
	{
		Event Player.HZMODE = 2;
		Set Ability 1 Enabled(Event Player, False);
		Wait(0.500, Ignore Condition);
		Loop If(Is Using Ability 2(Event Player) == True);
		Set Ability 1 Enabled(Event Player, True);
	}
}

rule("[한조] : 용의 눈으로 봐라 - 색 구슬")
{
	event
	{
		Player Took Damage;
		All;
		All;
	}

	condition
	{
		Attacker == Players On Hero(Hero(한조), All Teams);
		Players On Hero(Hero(한조), All Teams).HZMODE == 1;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Purple), Event Player, 1.800, Visible To Position and Radius);
		Event Player.P = Last Created Entity;
		Create Effect(All Players(All Teams), Sphere, Color(Purple), Event Player, 1.800, Visible To Position and Radius);
		Event Player.V = Last Created Entity;
		Create Effect(All Players(All Teams), Sphere, Color(Purple), Event Player, 1.800, Visible To Position and Radius);
		Event Player.N = Last Created Entity;
		Create Effect(All Players(All Teams), Sphere, Color(Purple), Event Player, 1.800, Visible To Position and Radius);
		Event Player.I = Last Created Entity;
		Create Effect(All Players(All Teams), Sphere, Color(Purple), Event Player, 1.800, Visible To Position and Radius);
		Event Player.L = Last Created Entity;
		Create Effect(All Players(All Teams), Sphere, Color(Purple), Event Player, 1.800, Visible To Position and Radius);
		Event Player.O = Last Created Entity;
		Create Effect(All Players(All Teams), Sphere, Color(Purple), Event Player, 1.800, Visible To Position and Radius);
		Event Player.H = Last Created Entity;
		Small Message(Victim, Custom String("{0} 한조 : 용의 눈으로 봐라!", Hero Icon String(Hero(한조))));
		Wait(1.500, Ignore Condition);
		Wait(6.500, Ignore Condition);
		Destroy Effect(Event Player.O);
		Destroy Effect(Event Player.H);
		Destroy Effect(Event Player.I);
		Destroy Effect(Event Player.L);
		Destroy Effect(Event Player.N);
		Destroy Effect(Event Player.P);
		Destroy Effect(Event Player.V);
	}
}

rule("[한조] : 용의 눈으로 봐라 - 얼음")
{
	event
	{
		Player Dealt Damage;
		All;
		한조;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Players On Hero(Hero(한조), All Teams).HZMODE == 1;
	}

	action
	{
		Set Status(Victim, Null, Frozen, 2.500);
	}
}

rule("[한조] : 넉백 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		한조;
	}

	condition
	{
		Players On Hero(Hero(한조), All Teams).HZMODE == 2;
	}

	action
	{
		Abort If Condition Is False;
		Apply Impulse(Victim, Position Of(Victim) - Position Of(Event Player), 15, To World, Cancel Contrary Motion);
		Small Message(Victim, Custom String("{0} 한조 : 무서워서 뒷걸음질하는 것인가...", Hero Icon String(Hero(한조))));
	}
}

rule("[한조] : 기본 공격 허용 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		한조;
	}

	condition
	{
		Is Using Ability 2(Event Player) == True;
	}

	action
	{
		Set Primary Fire Enabled(Event Player, True);
	}
}

rule("[한조] : 기본 공격 비허용 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		한조;
	}

	condition
	{
		Is Using Ability 2(Event Player) == False;
	}

	action
	{
		Set Primary Fire Enabled(Event Player, False);
	}
}

rule("[한조] : 용이여, 적들을 삼켜라 - 시야 조정, 궁극기 이펙트")
{
	event
	{
		Ongoing - Each Player;
		All;
		한조;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Event Player.HZMODE = 3;
		Start Facing(Event Player, Event Player + Position Of(Event Player) + Vector(0, 500, 0), 2400, To World, Direction and Turn Rate);
		Wait(0.500, Ignore Condition);
		Play Effect(All Players(All Teams), Ring Explosion, Color(Yellow), Position Of(Event Player) + Vector(0, 2, 0), 0.800);
		Play Effect(All Players(All Teams), Ring Explosion, Color(흰색), Position Of(Event Player) + Vector(0, 1.700, 0), 1);
		Play Effect(All Players(All Teams), Ring Explosion, Color(Yellow), Position Of(Event Player) + Vector(0, 1.400, 0), 2);
		Play Effect(All Players(All Teams), Ring Explosion, Color(흰색), Position Of(Event Player) + Vector(0, 0.800, 0), 2.700);
		Play Effect(All Players(All Teams), Ring Explosion, Color(Yellow), Position Of(Event Player) + Vector(0, 0.300, 0), 3.100);
		Wait(1, Ignore Condition);
		Stop Facing(Event Player);
	}
}

rule("[한조] : 용이여, 적들을 삼켜라 - 구름 이펙트 생성 및 스턴")
{
	event
	{
		Ongoing - Each Player;
		All;
		한조;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
		Is Alive(Event Player) == True;
		Has Spawned(Event Player) == True;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 한조 : 용이여, 적들을 삼켜라!", Hero Icon String(Hero(한조))));
		Wait(2.900, Ignore Condition);
		Event Player.P = Position Of(Event Player);
		Create Effect(All Players(All Teams), Cloud, Color(흰색), Event Player.P + Vector(0, 18, 0), 30, Visible To Position and Radius);
		Event Player.Y = Last Created Entity;
		Create Effect(All Players(All Teams), Cloud, Color(Yellow), Event Player.P + Vector(0, 16, 0), 25, Visible To Position and Radius);
		Event Player.X = Last Created Entity;
		Create Effect(All Players(All Teams), Cloud, Color(흰색), Event Player.P + Vector(0, 14, 0), 28, Visible To Position and Radius);
		Event Player.W = Last Created Entity;
		Small Message(All Players(All Teams), Custom String("{0} 한조 : 하늘의 기운이 심상치 않군.", Hero Icon String(Hero(한조))));
		Wait(Random Integer(1, 3.500), Ignore Condition);
		Small Message(All Players(All Teams), Custom String("{0} 한조 : 번개가 떨어진다.", Hero Icon String(Hero(한조))));
		Wait(Random Integer(1, 3.500), Ignore Condition);
		Event Player.HZQ = 1;
		Wait(0.100, Ignore Condition);
		Set Status(Filtered Array(All Players(All Teams), Current Array Element != Event Player), Event Player, Stunned, 4);
		Damage(Filtered Array(All Players(All Teams), Current Array Element != Event Player), Event Player, 100);
		Wait(3, Ignore Condition);
		Destroy Effect(Event Player.Y);
		Destroy Effect(Event Player.X);
		Destroy Effect(Event Player.W);
	}
}

rule("[한조] : 용이여, 적들을 삼켜라 - 번개 이펙트 생성")
{
	event
	{
		Ongoing - Each Player;
		All;
		한조;
	}

	condition
	{
		disabled Has Spawned(Event Player) == True;
		disabled Is Alive(Event Player) == True;
		disabled Is Using Ultimate(Event Player) == True;
		Event Player.HZQ == 1;
	}

	action
	{
		disabled Wait(6.800, Ignore Condition);
		Play Effect(All Players(All Teams), Ring Explosion Sound, Color(Yellow), All Players(All Teams), 30);
		Play Effect(All Players(All Teams), Ring Explosion Sound, Color(흰색), All Players(All Teams), 30);
		Create Beam Effect(All Players(All Teams), Good Beam, Event Player.P + Vector(Random Real(-12, 12), 30, Random Real(-8, 8)),
			Event Player.P + Vector(Random Real(4, -4), -1000, Random Real(4, -4)), Color(흰색), Visible To Position and Radius);
		Event Player.R = Last Created Entity;
		Wait(0.100, Ignore Condition);
		Create Beam Effect(All Players(All Teams), Bad Beam, Event Player.P + Vector(Random Real(-12, 12), 30, Random Real(-8, 8)),
			Event Player.P + Vector(Random Real(4, -4), -1000, Random Real(4, -4)), Color(Yellow), Visible To Position and Radius);
		Event Player.J = Last Created Entity;
		Wait(0.100, Ignore Condition);
		Create Beam Effect(All Players(All Teams), Bad Beam, Event Player.P + Vector(Random Real(-12, 12), 30, Random Real(-8, 8)),
			Event Player.P + Vector(Random Real(2, -2), -1000, Random Real(2, -2)), Color(Blue), Visible To Position and Radius);
		Event Player.T = Last Created Entity;
		Wait(0.100, Ignore Condition);
		Create Beam Effect(All Players(All Teams), Good Beam, Event Player.P + Vector(Random Real(-12, 12), 30, Random Real(-8, 8)),
			Event Player.P + Vector(Random Real(7, -7), -1000, Random Real(7, -7)), Color(흰색), Visible To Position and Radius);
		Event Player.D = Last Created Entity;
		Wait(0.100, Ignore Condition);
		Create Beam Effect(All Players(All Teams), Bad Beam, Event Player.P + Vector(Random Real(-12, 12), 30, Random Real(-8, 8)),
			Event Player.P + Vector(Random Real(2, -2), -1000, Random Real(2, -2)), Color(Yellow), Visible To Position and Radius);
		Event Player.F = Last Created Entity;
		Wait(0.100, Ignore Condition);
		Create Beam Effect(All Players(All Teams), Bad Beam, Event Player.P + Vector(Random Real(-12, -8), 30, Random Real(-12, -8)),
			Event Player.P + Vector(Random Real(5, -5), -1000, Random Real(5, -5)), Color(Blue), Visible To Position and Radius);
		Event Player.S = Last Created Entity;
		Wait(0.500, Ignore Condition);
		Destroy Effect(Event Player.R);
		Destroy Effect(Event Player.J);
		Destroy Effect(Event Player.T);
		Destroy Effect(Event Player.D);
		Destroy Effect(Event Player.F);
		Destroy Effect(Event Player.S);
		Event Player.HZQ = 2;
	}
}

rule("[한조] : 용이여, 적들을 삼켜라 - 번개 이펙트 삭제")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Match Round == 1;
	}

	action
	{
		Global.R = Custom String("오른쪽닭다리");
		Wait(0.500, Ignore Condition);
		Global.R = Custom String("빨대");
		Wait(0.500, Ignore Condition);
		Global.R = Custom String("Meihelpu");
		Wait(0.500, Ignore Condition);
		Global.R = Custom String("KDH3376");
		Wait(0.500, Ignore Condition);
		Global.R = Custom String("주거라주거라주거");
		Wait(0.500, Ignore Condition);
		Global.R = Custom String("전갑길");
		Wait(0.500, Ignore Condition);
		Global.R = Custom String("아또마끼");
		Wait(0.500, Ignore Condition);
		Global.R = Custom String("Aimdot76");
		Wait(0.500, Ignore Condition);
		Global.HUDS = Custom String("FIVE");
		Wait(0.500, Ignore Condition);
		Global.HUDS = Custom String("Hermè s");
		Wait(0.500, Ignore Condition);
		Global.HUDS = Custom String("금빛미키마우스");
		Wait(0.500, Ignore Condition);
		Global.HUDS = Custom String("비미비키");
		Wait(0.500, Ignore Condition);
		Global.HUDS = Custom String("OrOl");
		Wait(0.500, Ignore Condition);
		Global.HUDS = Custom String("우빈아나는어때씀");
		Wait(0.500, Ignore Condition);
		Global.HUDS = Custom String("gus1rms1");
		Wait(0.500, Ignore Condition);
	}
}

rule("[메이] : 능력 설명 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		메이;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create Progress Bar HUD Text(Players On Hero(Hero(메이), All Teams), 0.250 * Event Player.MD, Custom String("{0}/400",
			Event Player.MD), Left, 7, Color(Green), Color(흰색), Visible To Values and Color, Visible Never);
		Create HUD Text(Event Player, Custom String("{0}   스프레이", Ability Icon String(Hero(메이), Button(Primary Fire))), Null,
			Custom String(" 좌클릭 (딜을 250회 넣을 때까지 사용 가능/특전시 최대 400회)\r\n 스프레이를 뿌려 적을 아주 짧게 빙결시킬 수 있음"), Left, 6, Color(Green), Color(흰색),
			Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 5, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 다같이 얼음", Ability Icon String(Hero(메이), Button(Ability 1))), Null, Custom String(
			" SHIFT\r\n 좁은 범위의 주변 적들에게 2.5초간 빙결상태 부여                    "), Left, 4, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Create Effect(Event Player, Ring, Color(Blue), Event Player, 3.300, Visible To Position and Radius);
		Event Player.SA = Last Created Entity;
		Event Player.MD = 250;
	}
}

rule("[메이] 좌클릭 - 스프레이 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		메이;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Firing Primary(Event Player) == True;
		Event Player.MD > 0;
	}

	action
	{
		Event Player.MD = Event Player.MD + -1;
		Set Status(Victim, Null, Frozen, 0.020);
	}
}

rule("[메이] 스프레이 비허용 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		메이;
	}

	condition
	{
		Event Player.MD <= 0;
	}

	action
	{
		Set Primary Fire Enabled(Event Player, False);
	}
}

rule("[메이] : 다같이 얼음")
{
	event
	{
		Ongoing - Each Player;
		All;
		메이;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Event Player.M = Players Within Radius(Event Player, 3.300, Opposite Team Of(Team Of(Event Player)), Surfaces);
		Event Player.M = Filtered Array(Event Player.M, Current Array Element != Event Player);
		Damage(Filtered Array(Event Player.M, Current Array Element != Event Player), Event Player, 100);
		Play Effect(All Players(All Teams), Ring Explosion, Color(Sky Blue), Event Player, 3);
		Play Effect(All Players(All Teams), Ring Explosion, Color(Sky Blue), Event Player, 5);
		Set Status(Event Player.M, Event Player, Frozen, 2.500);
		Small Message(Event Player.M, Custom String("{0} 메이 : 손이 시려워, 꽁!", Hero Icon String(Hero(메이))));
	}
}

rule("[메이] : 죽으면 이펙트 삭제 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		메이;
	}

	condition
	{
		Is Dead(Event Player) == True;
	}

	action
	{
		Destroy Effect(Event Player.SA);
	}
}

rule("[바스티온] : 능력 설명 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		바스티온;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create Progress Bar HUD Text(Players On Hero(Hero(바스티온), All Teams), 10 * Event Player.BAS1, Custom String("{0}/10",
			Event Player.BAS1), Left, 7, Color(Green), Color(흰색), Visible To Values and Color, Visible Never);
		Create HUD Text(Event Player, Custom String("{0}  급속 전환", Ability Icon String(Hero(바스티온), Button(Ability 1))), Null, Custom String(
			" F (상호작용키, 경계 모드일 때 사용 가능, 최대 10번 사용 가능)\r\n 바라보고 있는 방향으로 0.2초간 가속하면서 즉시 수색 모드로 전환됨"), Left, 6, Color(Green), Color(흰색),
			Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 5, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 넉백", Ability Icon String(Hero(바스티온), Button(Primary Fire))), Null, Custom String(
			" 좌클릭\r\n 공격에 맞은 적에게 약간의 넉백효과 부여                           "), Left, 3, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 2.500, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 포격", Ability Icon String(Hero(바스티온), Button(Primary Fire))), Null, Custom String(
			" Q\r\n 1. 포격에 맞은 적에게 보다 큰 넉백효과 부여                            \n 2. 포격에 맞은 적에게 1초간 스턴상태 부여"), Left, 2, Color(Green), Color(흰색),
			Color(흰색), None, Visible Never);
		Event Player.BAS1 = 10;
	}
}

rule("[바스티온] : 기본공격 - 넉백")
{
	event
	{
		Player Dealt Damage;
		All;
		바스티온;
	}

	condition
	{
		Is Firing Primary(Players On Hero(Hero(바스티온), All Teams)) == True;
	}

	action
	{
		Abort If Condition Is False;
		Apply Impulse(Victim, Position Of(Victim) - Position Of(Event Player), 9, To World, Cancel Contrary Motion);
	}
}

rule("[바스티온] : 궁극기 - 넉백")
{
	event
	{
		Player Dealt Damage;
		All;
		바스티온;
	}

	condition
	{
		Is Using Ultimate(Players On Hero(Hero(바스티온), All Teams)) == True;
	}

	action
	{
		Abort If Condition Is False;
		Apply Impulse(Victim, Position Of(Victim) - Position Of(Event Player), 40, To World, Cancel Contrary Motion);
		Set Status(Victim, Null, Stunned, 1);
	}
}

rule("[바스티온] : 급속 전환 1 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		바스티온;
	}

	condition
	{
		Is Alive(Event Player) == True;
		Is Button Held(Event Player, Button(Interact)) == True;
		Has Status(Event Player, Hacked) == False;
		Has Status(Event Player, Rooted) == False;
		Event Player.ALT == 1;
		Event Player.BAS1 > 0;
		Has Status(Event Player, Hacked) == False;
		Has Status(Event Player, Knocked Down) == False;
		Has Status(Event Player, Asleep) == False;
		Has Status(Event Player, Frozen) == False;
		Has Status(Event Player, Rooted) == False;
		Has Status(Event Player, Stunned) == False;
	}

	action
	{
		Apply Impulse(Event Player, Facing Direction Of(Event Player), 50, To World, Cancel Contrary Motion);
		Event Player.BAS1 = Event Player.BAS1 + -1;
		Press Button(Event Player, Button(Ability 1));
		Event Player.ALT = 0;
	}
}

rule("[바스티온] : 급속 전환 2 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		바스티온;
	}

	condition
	{
		Is In Alternate Form(Event Player) == True;
	}

	action
	{
		Wait(1, Ignore Condition);
		Event Player.ALT = 1;
	}
}

rule("[바스티온] : 급속 전환 3 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		바스티온;
	}

	condition
	{
		Is In Alternate Form(Event Player) == False;
	}

	action
	{
		Event Player.ALT = 0;
	}
}

rule("[토르비욘] : 능력 설명 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		토르비욘;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Set Ammo(Event Player, 0, 3);
		Set Max Ammo(Event Player, 0, 3);
		Create HUD Text(Event Player, Custom String("{0}       넉백", Icon String(Dizzy)), Null, Custom String(
			" 좌클릭 (망치)\r\n 망치에 맞은 적에게 넉백효과 부여                         "), Left, 9, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 8, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}    스턴", Ability Icon String(Hero(토르비욘), Button(Secondary Fire))), Null,
			Custom String(" 좌클릭 (총알)\r\n 총알에 맞은 적에게 스턴상태 부여                         "), Left, 7, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 6, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 화염방사기", Icon String(Fire)), Null, Custom String(
			" E (스킬 사용 시간 동안 좌클릭 불가)\n 맞은 적에게 넉백과 시야방해, 5초간 화상상태 부여          "), Left, 5, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 4, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 짧은다리의 역습", Hero Icon String(Hero(토르비욘))), Null, Custom String(
			" 패시브\r\n 1. 다른 영웅들보다 이동속도가 느림                    \r\n 2. 주변의 적들에게 화상상태 부여"), Left, 3, Color(Green), Color(흰색), Color(흰색),
			None, Visible Never);
	}
}

rule("[토르비욘] : 패시브 - 이펙트")
{
	event
	{
		Ongoing - Each Player;
		All;
		토르비욘;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Create Effect(Filtered Array(All Players(All Teams), Current Array Element != Event Player), Cloud, Color(Red), Position Of(
			Event Player), 2.200, Visible To Position and Radius);
	}
}

rule("[토르비욘] : 과부하 - 화상, 상시 발동")
{
	event
	{
		Ongoing - Each Player;
		All;
		토르비욘;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		disabled Start Holding Button(Event Player, Button(Ability 2));
		Event Player.Q = Players Within Radius(Event Player, 2.200, Opposite Team Of(Team Of(Event Player)), Surfaces);
		Event Player.Q = Filtered Array(Event Player.Q, Current Array Element != Event Player);
		Set Status(Event Player.Q, Event Player, Burning, 1.500);
		Wait(0.016, Ignore Condition);
		Loop;
	}
}

rule("[토르비욘] : 총알공격 - 스턴 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		토르비욘;
	}

	condition
	{
		Is In Alternate Form(Event Player) == False;
		Is Using Ability 2(Event Player) == False;
	}

	action
	{
		Abort If Condition Is False;
		Set Status(Victim, Null, Stunned, 0.333);
		Small Message(Victim, Custom String("{0} 토르비욘 : 멈춰!", Hero Icon String(Hero(토르비욘))));
	}
}

rule("[토르비욘] : 망치공격 - 넉백 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		토르비욘;
	}

	condition
	{
		Is In Alternate Form(Event Player) == True;
		Is Using Ability 2(Event Player) == False;
	}

	action
	{
		Abort If Condition Is False;
		Apply Impulse(Victim, Position Of(Victim) - Position Of(Event Player), 20, To World, Cancel Contrary Motion);
		Small Message(Victim, Custom String("{0} 토르비욘 : 저리가!", Hero Icon String(Hero(토르비욘))));
	}
}

rule("[토르비욘] : 과부하 사용시 좌클릭 비활성화 by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		토르비욘;
	}

	condition
	{
		Is Using Ability 2(Event Player) == True;
	}

	action
	{
		Disallow Button(Event Player, Button(Primary Fire));
	}
}

rule("[토르비욘] : 과부하 미사용시 좌클릭 활성화 by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		토르비욘;
	}

	condition
	{
		Is Using Ability 2(Event Player) == False;
	}

	action
	{
		Allow Button(Event Player, Button(Primary Fire));
		All Players(All Teams).TOR_FIRED = 0;
	}
}

rule("[토르비욘] : 화염방사기 발동 by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		토르비욘;
	}

	condition
	{
		Is Using Ability 2(Event Player) == True;
		Has Status(Event Player, Hacked) == False;
		Has Status(Event Player, Knocked Down) == False;
		Has Status(Event Player, Asleep) == False;
		Has Status(Event Player, Frozen) == False;
		Has Status(Event Player, Stunned) == False;
	}

	action
	{
		투사체 생성(구형 투사체, Event Player, Eye Position(Event Player) + Vector(0, 1.500, 0), Direction From Angles(
			Horizontal Angle From Direction(Facing Direction Of(Event Player)) + Random Real(-15, 15), Vertical Angle From Direction(
			Facing Direction Of(Event Player)) + Random Real(-5, 5)), To World, Damage, All Teams, 1, 1, 2, Bad Explosion, Explosion Sound,
			0.050, 50, 1, 5, 0, Random Real(25, 50));
		Wait(0.050, Ignore Condition);
		Loop If Condition Is True;
	}
}

rule("[토르비욘] : 화염방사기 화상상태 by Dote6")
{
	event
	{
		Player Dealt Damage;
		All;
		토르비욘;
	}

	condition
	{
		Is Using Ability 2(Event Player) == True;
	}

	action
	{
		Set Status(Victim, Null, Burning, 5);
	}
}

rule("[토르비욘] : 화염방사기 시야방해 by Dote6")
{
	event
	{
		Player Dealt Damage;
		All;
		토르비욘;
	}

	condition
	{
		Is Using Ability 2(Event Player) == True;
		Victim.TOR_FIRED != 1;
	}

	action
	{
		Victim.TOR_FIRED = 1;
		Create Effect(All Players(All Teams), Sphere, Color(Red), Eye Position(Victim), 0.500, Visible To Position and Radius);
		Victim.TOR_EFFECT1 = Last Created Entity;
		Create Effect(All Players(All Teams), Sphere, Color(Red), Eye Position(Victim), 0.500, Visible To Position and Radius);
		Victim.TOR_EFFECT2 = Last Created Entity;
		Create Effect(All Players(All Teams), Sphere, Color(Red), Eye Position(Victim), 0.500, Visible To Position and Radius);
		Victim.TOR_EFFECT3 = Last Created Entity;
		Wait(5, Ignore Condition);
		Wait Until(Victim.TOR_FIRED == 0, 99999);
		Destroy Effect(Victim.TOR_EFFECT1);
		Destroy Effect(Victim.TOR_EFFECT2);
		Destroy Effect(Victim.TOR_EFFECT3);
	}
}

rule("[겐지] : 능력 설명 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		겐지;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0}             질주", Ability Icon String(Hero(겐지), Button(Ability 2))), Null,
			Custom String(" E\r\n 일시적으로 이동속도 증가                                                    "), Left, 8, Color(Green), Color(흰색),
			Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}          질풍참", Ability Icon String(Hero(겐지), Button(Ability 1))), Null,
			Custom String(" SHIFT\r\n 1. 데스노트가 가장 적게 남은 플레이어에게 순간이동                        \r\n 2. 궁극기로 처치 시 질풍참 쿨타임 초기화 "), Left, 6,
			Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 5, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}             은신", Icon String(Eye)), Null, Custom String(
			" 패시브\r\n 상태변화 효과를 받지 않고 움직임이 없으면 은신상태가 됨     "), Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 데스블레이드", Ability Icon String(Hero(겐지), Button(Ultimate))), Null, Custom String(
			" Q\r\n 1. 궁극기에 맞은 적에게 넉백 효과 부여                                                          \r\n 2. 적이 궁극기에 6번 맞으면 즉시 사망"), Left,
			2, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Set Primary Fire Enabled(Event Player, False);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Right, 2.500, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 데스노트", Icon String(Poison)), Null, Null, Right, 2, Color(Red), Color(흰색), Color(
			흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Right, 1.500, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
	}
}

rule("[겐지] : 패시브 - 이펙트")
{
	event
	{
		Ongoing - Each Player;
		All;
		겐지;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create Effect(Filtered Array(All Players(All Teams), Current Array Element != Event Player), Bad Aura, Color(Green), Event Player,
			1, Visible To Position and Radius);
		Event Player.Y = Last Created Entity;
	}
}

rule("[겐지] : 패시브 - 투명 1 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		겐지;
	}

	condition
	{
		Is Moving(Event Player) == False;
		Has Status(Event Player, Hacked) == False;
		Has Status(Event Player, Burning) == False;
		Has Status(Event Player, Knocked Down) == False;
		Has Status(Event Player, Asleep) == False;
		Has Status(Event Player, Frozen) == False;
		Has Status(Event Player, Rooted) == False;
		Has Status(Event Player, Stunned) == False;
	}

	action
	{
		Set Invisible(Event Player, All);
	}
}

rule("[겐지] : 패시브 - 투명 2")
{
	event
	{
		Ongoing - Each Player;
		All;
		겐지;
	}

	condition
	{
		Is Alive(Event Player) == True;
		Is Moving(Event Player) == True;
	}

	action
	{
		Set Invisible(Event Player, None);
	}
}

rule("[겐지] : 패시브 - 투명 3 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		겐지;
	}

	condition
	{
		Is Alive(Event Player) == True;
		(Has Status(Event Player, Hacked) || Has Status(Event Player, Burning) || Has Status(Event Player, Knocked Down) || Has Status(
			Event Player, Asleep) || Has Status(Event Player, Frozen) || Has Status(Event Player, Rooted) || Has Status(Event Player,
			Stunned)) == True;
	}

	action
	{
		Set Invisible(Event Player, None);
	}
}

rule("[겐지] : 질풍참 - 발동 by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Is Using Ability 1(Players On Hero(Hero(겐지), All Teams)) == True;
		Is Alive(Event Player) == True;
		Hero Of(Event Player) != Hero(겐지);
		Has Spawned(Event Player) == True;
		Event Player.Z != 1;
	}

	action
	{
		If(Event Player.GD == 1);
			Wait(0.020, Ignore Condition);
			Global.GD_playerarray = Append To Array(Global.GD_playerarray, Event Player);
		Else If(Event Player.GD == 2);
			Wait(0.040, Ignore Condition);
			Global.GD_playerarray = Append To Array(Global.GD_playerarray, Event Player);
		Else If(Event Player.GD == 3);
			Wait(0.060, Ignore Condition);
			Global.GD_playerarray = Append To Array(Global.GD_playerarray, Event Player);
		Else If(Event Player.GD == 4);
			Wait(0.080, Ignore Condition);
			Global.GD_playerarray = Append To Array(Global.GD_playerarray, Event Player);
		Else If(Event Player.GD == 5);
			Wait(0.100, Ignore Condition);
			Global.GD_playerarray = Append To Array(Global.GD_playerarray, Event Player);
		Else;
			Wait(0.120, Ignore Condition);
			Global.GD_playerarray = Append To Array(Global.GD_playerarray, Event Player);
	}
}

rule("[겐지] : 질풍참 - 순간이동 by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		겐지;
	}

	condition
	{
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Global.GD_playerarray = Empty Array;
		Wait(0.300, Ignore Condition);
		If(Global.GD_playerarray != Empty Array);
			Teleport(Event Player, Position Of(Global.GD_playerarray[0]) + Vector(0, 0.600, 0));
			Wait(0.100, Ignore Condition);
			Set Facing(Event Player, Vector Towards(Event Player, Global.GD_playerarray[0] + Vector(0, 0.600, 0)), To World);
	}
}

rule("[겐지] : 튕겨내기 - 질주")
{
	event
	{
		Ongoing - Each Player;
		All;
		겐지;
	}

	condition
	{
		Is Using Ability 2(Event Player) == True;
		Has Spawned(Event Player) == True;
	}

	action
	{
		Set Move Speed(Event Player, 300);
		Wait(1.800, Ignore Condition);
		Set Move Speed(Event Player, 120);
	}
}

rule("[겐지] : 궁극기 - 넉백 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		겐지;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
		Is Using Ability 2(Event Player) == False;
		Victim.GD > 0;
	}

	action
	{
		Abort If Condition Is False;
		Apply Impulse(Victim, Position Of(Victim) - Position Of(Event Player), 40, To World, Cancel Contrary Motion);
		Victim.GD = Victim.GD + -1;
		Small Message(Victim, Custom String("{0} 겐지 : 내 용검 맛이 어떠느냐", Hero Icon String(Hero(겐지))));
	}
}

rule("[겐지] : 궁극기 - 횟수 표시 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Hero Of(Event Player) != Hero(겐지);
	}

	action
	{
		Create HUD Text(Players On Hero(Hero(겐지), All Teams), Custom String("{0} {1}회 남음", Hero Icon String(Hero Of(Event Player)),
			Event Player.GD), Null, Null, Right, 3, Color(흰색), Color(흰색), Color(Red), Visible To and String, Default Visibility);
		Event Player.G_GAGE_H = Last Text ID;
	}
}

rule("[겐지] : 궁극기 - 게이지 표시 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Has Spawned(Players On Hero(Hero(겐지), All Teams)) == True;
	}

	action
	{
		Event Player.GD = 6;
		Create Progress Bar HUD Text(Filtered Array(Event Player, Current Array Element != Players On Hero(Hero(겐지), All Teams)),
			16.666 * Event Player.GD, Custom String("{1} 겐지의 궁극기에 {0}번 더 공격받으면 즉시 사망", Event Player.GD, Hero Icon String(Hero(겐지))), Top,
			5, Color(Red), Color(흰색), Visible To Values and Color, Default Visibility);
		Event Player.G_GAGE = Last Text ID;
	}
}

rule("[겐지] : 궁극기 - 사망 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Event Player.GD <= 0;
	}

	action
	{
		Kill(Event Player, Players On Hero(Hero(겐지), All Teams));
		Small Message(Event Player, Custom String("{0} 겐지 : 내 용검으로 죽은걸 영광스러워해라", Hero Icon String(Hero(겐지))));
		If(Is Using Ultimate(Players On Hero(Hero(겐지), All Teams)) == True);
			Set Ability Cooldown(Event Player, Button(Ability 1), 0);
			Small Message(Players On Hero(Hero(겐지), All Teams), Custom String("질풍참 사용 가능"));
	}
}

rule("[겐지] : 궁극기 - 사망시 게이지 삭제 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Is Dead(Players On Hero(Hero(겐지), All Teams)) == True;
	}

	action
	{
		Destroy Progress Bar HUD Text(Event Player.G_GAGE);
	}
}

rule("[겐지] : 궁극기 - 퇴장시 게이지 삭제 by KISUM")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Entity Exists(Players On Hero(Hero(겐지), All Teams)) == False;
	}

	action
	{
		Destroy Progress Bar HUD Text(All Players(All Teams).G_GAGE);
	}
}

rule("[겐지] : 궁극기 - 부활시 횟수 표시 by KISUM (버그수정)")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Event Player.RV_GAGE == 1;
		Hero Of(Event Player) != Hero(겐지);
	}

	action
	{
		Event Player.GD = 3;
		Create HUD Text(Players On Hero(Hero(겐지), All Teams), Custom String("{0} {1}회 남음", Hero Icon String(Hero Of(Event Player)),
			Event Player.GD), Null, Null, Right, 3, Color(흰색), Color(흰색), Color(Red), Visible To and String, Default Visibility);
		Event Player.G_GAGE_H = Last Text ID;
	}
}

rule("[겐지] : 궁극기 - 부활시 게이지 표시 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Players On Hero(Hero(겐지), All Teams).RV_GAGE == 1;
	}

	action
	{
		Create Progress Bar HUD Text(Filtered Array(Event Player, Current Array Element != Players On Hero(Hero(겐지), All Teams)),
			16.666 * Event Player.GD, Custom String("{1} 겐지의 궁극기에 {0}번 더 공격받으면 즉시 사망", Event Player.GD, Hero Icon String(Hero(겐지))), Top,
			5, Color(Red), Color(흰색), Visible To Values and Color, Default Visibility);
		Event Player.G_GAGE = Last Text ID;
	}
}

rule("[겐지] : 궁극기 - 횟수 표시 삭제 1 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Is Alive(Event Player) == False;
	}

	action
	{
		Destroy HUD Text(Event Player.G_GAGE_H);
	}
}

rule("[겐지] : 궁극기 - 횟수 표시 삭제 2 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Event Player == Players On Hero(Hero(겐지), All Teams);
	}

	action
	{
		Destroy HUD Text(Event Player.G_GAGE_H);
	}
}

rule("[겐지] : 바티스트 불사 장치 사망 X 해결 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		바티스트;
	}

	condition
	{
		Is Alive(Event Player) == True;
		Event Player.GD <= 0;
	}

	action
	{
		Wait(0.250, Ignore Condition);
		Abort If Condition Is False;
		Event Player.GD = 1;
	}
}

rule("[솔저: 76] : 능력 설명 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		솔저: 76;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0}    시간 증가", Ability Icon String(Hero(솔저: 76), Button(Ability 2))), Null,
			Custom String(" E (라운드시간 4초 미만시 사용 가능)                                                           \r\n 라운드시간을 4초로 세팅"), Left, 6,
			Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 5, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 전술 조준경", Ability Icon String(Hero(솔저: 76), Button(Ultimate))), Null,
			Custom String(" Q\r\n 1. 모든 적들을 8초간 강제로 앉게 함\r\n 2. 공격에 맞은 적에게 0.3초간 스턴상태 부여                    "), Left, 4, Color(Green),
			Color(흰색), Color(흰색), None, Visible Never);
	}
}

rule("[솔저: 76] : 전술조준경 - 강제 앉기")
{
	event
	{
		Ongoing - Each Player;
		All;
		솔저: 76;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Set Primary Fire Enabled(Event Player, False);
		Start Holding Button(Filtered Array(All Players(All Teams), Current Array Element != Event Player), Button(Crouch));
		Big Message(All Players(All Teams), Custom String("{0} 솔저: 76 : 총알 날아간다, 모두 머리 숙여!", Hero Icon String(Hero(솔저: 76))));
		Wait(8, Ignore Condition);
		Stop Holding Button(All Players(All Teams), Button(Crouch));
	}
}

rule("[솔저: 76] : 전술조준경 - 사망시 강제 앉기 해제 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		솔저: 76;
	}

	condition
	{
		Is Dead(Event Player) == True;
	}

	action
	{
		Stop Holding Button(All Players(All Teams), Button(Crouch));
	}
}

rule("[솔저: 76] : 전술조준경 - 퇴장시 강제 앉기 해제 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		솔저: 76;
	}

	condition
	{
		Entity Exists(Event Player) == False;
	}

	action
	{
		Stop Holding Button(All Players(All Teams), Button(Crouch));
	}
}

rule("[솔저: 76] : 전술조준경 - 스턴 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		솔저: 76;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Set Status(Victim, Null, Stunned, 0.300);
	}
}

rule("[솔저: 76] : 시간 증가 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		솔저: 76;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Is Using Ability 2(Event Player) == True;
		Match Time < 4;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 솔저: 76 : 신에게는 아직도 4초가 남아있습니다.", Hero Icon String(Hero(솔저: 76))));
		Set Match Time(4);
	}
}

rule("[시그마] : 능력 설명 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		시그마;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0}  저중력 붕괴", Ability Icon String(Hero(시그마), Button(Ability 1))), Null, Custom String(
			" SHIFT (에임 필요)\r\n 조준선에서 가장 가까운 적을 잠깐동안 공중에 띄움"), Left, 8, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}     즉시 회복", Icon String(Plus)), Null, Custom String(
			" 패시브 2\r\n 적에 의해 궁극기 게이지가 감소되더라도 즉시 회복"), Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 내면의 인격", Hero Icon String(Hero(시그마))), Null, Custom String(
			" 패시브 1\r\n 내면의 인격이 조금씩 새어나와 궁극기가 형성됨 (총 2회)"), Left, 2, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
	}
}

rule("[시그마] : 키네틱 손아귀 - 순간 역중력 (특전관련 수정)")
{
	event
	{
		Ongoing - Each Player;
		All;
		시그마;
	}

	condition
	{
		Is Using Ability 1(Event Player) == True;
		Event Player.ttek_right_enable != True;
	}

	action
	{
		Damage(Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams)
			!= Is Dead(Player Closest To Reticle(Event Player, All Teams))), Event Player, 100);
		Apply Impulse(Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams)
			!= Is Dead(Player Closest To Reticle(Event Player, All Teams))), Vector(0, 3, 0), 15, To Player, Cancel Contrary Motion);
		disabled All Living Players(All Teams).S = 0;
	}
}

rule("[시그마] : 중력붕괴 - 시그마에게 환청")
{
	event
	{
		Ongoing - Each Player;
		All;
		시그마;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Set Ultimate Ability Enabled(Event Player, False);
		Wait(5, Ignore Condition);
		Small Message(Event Player, Custom String("{0} 시그마 : 으음? 이게 무슨 소리지..?", Hero Icon String(Hero(시그마))));
		Set Status(Event Player, Null, Rooted, 1);
		Wait(25, Ignore Condition);
		Small Message(Event Player, Custom String("{0} 시그마 : 시끄러워! 너 누구야, 당장 나와!", Hero Icon String(Hero(시그마))));
		Set Status(Event Player, Null, Rooted, 1.500);
		Wait(20, Ignore Condition);
		Small Message(Event Player, Custom String("{0} 시그마 : 제발... 제발... 제발 그만해!", Hero Icon String(Hero(시그마))));
		Set Status(Event Player, Null, Rooted, 1.750);
		Wait(15, Ignore Condition);
		Small Message(Event Player, Custom String("{0} 시그마 : 꺼져! 당장 내 머릿속에서 꺼지란 말야!!", Hero Icon String(Hero(시그마))));
		Set Status(Event Player, Null, Stunned, 2);
		Wait(10, Ignore Condition);
		Small Message(Event Player, Custom String("{0} 시그마 : ...우주가, 내게 노래하고 있어!", Hero Icon String(Hero(시그마))));
		Set Ultimate Ability Enabled(Event Player, True);
		Create Effect(All Players(All Teams), Cloud, Color(흰색), Position Of(Event Player), 1.500, Visible To Position and Radius);
		Set Ultimate Charge(Event Player, 100);
		Wait Until(Is Using Ultimate(Event Player), 99999);
		Set Ultimate Ability Enabled(Event Player, False);
		Wait(25, Ignore Condition);
		Small Message(Event Player, Custom String("{0} 시그마 : 으음? 내게 무슨 일이 있었던거지?", Hero Icon String(Hero(시그마))));
		Set Status(Event Player, Null, Rooted, 1.500);
		Wait(20, Ignore Condition);
		Small Message(Event Player, Custom String("{0} 시그마 : 기억이 났어... 너 대체 누구야!", Hero Icon String(Hero(시그마))));
		Set Status(Event Player, Null, Rooted, 1.750);
		Wait(15, Ignore Condition);
		Small Message(Event Player, Custom String("{0} 시그마 : 도대체 나한테 이러는 이유가 뭐야!", Hero Icon String(Hero(시그마))));
		Set Status(Event Player, Null, Rooted, 2);
		Wait(10, Ignore Condition);
		Small Message(Event Player, Custom String("{0} 시그마 : 또 다시 우주가, 내게 노래하고 있어!", Hero Icon String(Hero(시그마))));
		Set Ultimate Ability Enabled(Event Player, True);
		Create Effect(All Players(All Teams), Cloud, Color(Blue), Position Of(Event Player), 1.500, Visible To Position and Radius);
		Set Ultimate Charge(Event Player, 100);
	}
}

rule("[시그마] : 궁극기 게이지 감소 무시 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		시그마;
	}

	condition
	{
		Ultimate Charge Percent(Event Player) > 0;
		Ultimate Charge Percent(Event Player) < 100;
	}

	action
	{
		Set Ultimate Charge(Event Player, 100);
	}
}

rule("[메르시] : 능력 설명 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		메르시;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create Progress Bar HUD Text(Players On Hero(Hero(메르시), All Teams), 5 * Event Player.MER, Custom String("{0}/20",
			Event Player.MER), Left, 9, Color(Green), Color(흰색), Values, Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 무빙", Ability Icon String(Hero(메르시), Button(Melee))), Null, Custom String(
			" 근접공격 (최대 20번 사용 가능)\r\n 1. 바라보고 있는 방향으로 0.15초간 가속한 후 0.45초간 스턴상태       \r\n 2. 공격을 받은 적에게 0.9초간 스턴상태 부여"), Left, 8, Color(
			Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 타인 부활 {1}", Ability Icon String(Hero(메르시), Button(Ability 2)), Global.MRSO), Null,
			Custom String(
			" R (재장전, 셀 제시 전 사용 가능, 기본 1회/특전 2회)\r\n 1. 사망한 다른 플레이어를 부활시킴\r\n 2. 9라운드가 되기 전 미사용 시 메르시 사망                              "),
			Left, 4, Color(Green), Color(흰색), Color(흰색), String, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 자기 부활 {1}", Ability Icon String(Hero(메르시), Button(Ability 2)), Global.MRSS), Null,
			Custom String(
			" 패시브 (9라운드가 되기 전 사망시 단 한번 부활)\r\n 1. 부활 이후 15초간 무적상태\r\n 2. 부활 이후 궁극기 사용 불가 및 무빙 횟수가 0이 됨                            "), Left,
			2, Color(Green), Color(흰색), Color(흰색), String, Visible Never);
		Event Player.MER = 20;
		Global.MRSS = 1;
		Global.MRSO = 1;
	}
}

rule("[메르시] : 패시브 - 부활 | 패자부활전 별도 with Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		메르시;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Event Player.mercypassive_once != 1;
	}

	action
	{
		Set Status(Event Player, Null, Unkillable, 9999);
		Event Player.mercypassive_once = 1;
	}
}

rule("[메르시] : 패시브 - 부활 2 with KISUM (폭넓게 수정)")
{
	event
	{
		Ongoing - Each Player;
		All;
		메르시;
	}

	condition
	{
		Health(Event Player) <= 500;
		Global.RoundNumber < 9;
		Health(Event Player) > 0;
	}

	action
	{
		Set Player Health(Event Player, 625);
		Set Status(Event Player, Null, Knocked Down, 2.500);
		Create Effect(Filtered Array(All Players(All Teams), Current Array Element != Position Of(Event Player)), Ring, Color(Yellow),
			Event Player, 1, Visible To Position and Radius);
		Event Player.M = Last Created Entity;
		Play Effect(All Players(All Teams), Good Pickup Effect, Color(Yellow), Event Player, 2);
		Play Effect(All Players(All Teams), Ring Explosion, Color(흰색), Event Player, 3);
		Set Ultimate Ability Enabled(Event Player, False);
		Global.MRSS = 0;
		Event Player.MER = 0;
		Big Message(All Players(All Teams), Custom String("{0} 메르시 : 영웅은 죽지 않아요!", Hero Icon String(Hero(메르시))));
		Wait(1.500, Ignore Condition);
		Clear Status(Event Player, Unkillable);
		If(Event Player.Z != 1);
			Small Message(Event Player, Custom String("{0} 메르시 : 다시 시작해보는거야!", Hero Icon String(Hero(메르시))));
		End;
		Set Status(Event Player, Null, Phased Out, 15);
		Event Player.GD = 3;
		Create Effect(Filtered Array(All Players(All Teams), Current Array Element != Position Of(Event Player)), Good Aura, Color(Yellow),
			Event Player, 1, Visible To Position and Radius);
		Event Player.M2 = Last Created Entity;
		Wait(15, Ignore Condition);
		Destroy Effect(Event Player.M2);
	}
}

rule("[메르시] : 패시브 - 부활 3 with KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		메르시;
	}

	condition
	{
		Global.RoundNumber >= 9;
	}

	action
	{
		Clear Status(Event Player, Unkillable);
		Global.MRSS = 0;
	}
}

rule("[메르시] : 타인 부활 1 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		메르시;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Event Player.Z != 1;
		Is Button Held(Event Player, Button(Reload)) == True;
		Global.MRSO > 0;
		Number Of Dead Players(All Teams) > 0;
		Match Time > 60;
		Has Status(Event Player, Hacked) == False;
		Has Status(Event Player, Knocked Down) == False;
		Has Status(Event Player, Asleep) == False;
		Has Status(Event Player, Frozen) == False;
		Has Status(Event Player, Stunned) == False;
	}

	action
	{
		Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams) == Is Dead(
			Player Closest To Reticle(Event Player, All Teams))).MV = 1;
	}
}

rule("[메르시] : 타인 부활 2 by KISUM with Dote6 (특전관련 수정)")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Event Player.MV == 1;
		Event Player.Z == 0;
	}

	action
	{
		Global.MRSO += -1;
		Resurrect(Event Player);
		If(Event Player.ZRV == 0 && Hero Of(Event Player) != Hero(자리야));
			Destroy HUD Text(Event Player.Z_GAGE_H);
			Wait(0.016, Ignore Condition);
			Create HUD Text(Players On Hero(Hero(자리야), All Teams), Custom String("{0} 사용가능", Hero Icon String(Hero Of(Event Player)),
				Ability Icon String(Hero(자리야), Button(Ability 2))), Null, Null, Right, 3, Color(흰색), Color(흰색), Color(Red),
				Visible To and String, Default Visibility);
			Event Player.Z_GAGE_H = Last Text ID;
		End;
		disabled If(Players On Hero(Hero(젠야타), All Teams).ZYTGAGE < 8 * (-1 + Global.RoundNumber));
		disabled Players On Hero(Hero(젠야타), All Teams).ZYTGAGE = 8 * (-1 + Global.RoundNumber);
		disabled End;
		Enable Death Spectate All Players(Event Player);
		Global.LivingPlayers = Append To Array(Global.LivingPlayers, Event Player);
		Create Effect(Filtered Array(All Players(All Teams), Current Array Element != Position Of(Event Player)), Ring, Color(Yellow),
			Event Player, 1, Visible To Position and Radius);
		Event Player.M = Last Created Entity;
		Play Effect(All Players(All Teams), Good Pickup Effect, Color(Yellow), Event Player, 2);
		Play Effect(All Players(All Teams), Ring Explosion, Color(흰색), Event Player, 3);
		Small Message(Event Player, Custom String("{0} {1}님이 당신을 부활시켰습니다.", Hero Icon String(Hero(메르시)), Custom String("{0}",
			Players On Hero(Hero(메르시), All Teams))));
		Big Message(All Players(All Teams), Custom String("{0} 메르시 : {1} {2}님! 일어나세요!", Hero Icon String(Hero(메르시)), Hero Icon String(
			Hero Of(Event Player)), Custom String("{0}", Event Player)));
		Communicate(Event Player, Thanks);
		Event Player.MV = 0;
		Event Player.RV_GAGE = 1;
		Wait Until(Match Time < 60, 999999);
		If(Is Alive(Event Player) == True);
			Set Player Score(Event Player, Global.RoundNumber);
		End;
	}
}

rule("[메르시] : 타인 부활 실패 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		메르시;
	}

	condition
	{
		Global.RoundNumber == 9;
		Global.MRSO > 0;
	}

	action
	{
		Wait(0.250, Ignore Condition);
		Kill(Event Player, Event Player);
	}
}

rule("[메르시] : 패시브 - 부활 후 죽으면 이펙트 삭제 (모든 영웅)")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Is Dead(Event Player) == True;
	}

	action
	{
		Destroy Effect(Event Player.M);
		Destroy Effect(Event Player.M2);
	}
}

rule("[메르시] : 시체표시 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Is Dead(Event Player) == True;
	}

	action
	{
		Create In-World Text(Players On Hero(Hero(메르시), All Teams), Custom String("{0} {1}의 시체", Hero Icon String(Hero Of(Event Player)),
			Custom String("{0}", Event Player)), Event Player, 1, Clip Against Surfaces, None, Color(Yellow), Default Visibility);
		Event Player.MSDP = Last Text ID;
	}
}

rule("[메르시] : 시체표시 제거 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		(Is Dead(Event Player) || Global.MRSO) == False;
	}

	action
	{
		Destroy In-World Text(Event Player.MSDP);
	}
}

rule("[메르시] : 무빙 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		메르시;
	}

	condition
	{
		Is Alive(Event Player) == True;
		Is Meleeing(Event Player) == True;
		Has Status(Event Player, Hacked) == False;
		Has Status(Event Player, Rooted) == False;
	}

	action
	{
		Apply Impulse(Event Player, Facing Direction Of(Event Player), 75, To World, Cancel Contrary Motion);
		Event Player.MER = Event Player.MER + -1;
		Play Effect(All Players(All Teams), Good Explosion, Color(Yellow), Event Player, 2);
		Wait(0.150, Ignore Condition);
		Set Status(Event Player, Null, Stunned, 0.450);
	}
}

rule("[메르시] : 무빙 - 스턴 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		메르시;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Is Meleeing(Event Player) == True;
	}

	action
	{
		Set Status(Victim, Null, Stunned, 0.900);
		Small Message(Victim, Custom String("{0} 메르시 : 비켜!", Hero Icon String(Hero(메르시))));
	}
}

rule("[메르시] : 무빙 불가 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		메르시;
	}

	condition
	{
		Is Alive(Event Player) == True;
		Event Player.MER == 0;
	}

	action
	{
		Set Melee Enabled(Event Player, False);
	}
}

rule("[솜브라] : 능력 설명 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		솜브라;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 색깔확인", Ability Icon String(Hero(솜브라), Button(Secondary Fire))), Null,
			Custom String(" R (재장전)\r\n 경기도의 딸 KISUM이 현재 라운드의 색깔을 알려줌                    "), Left, 8, Color(Green), Color(흰색), Color(흰색),
			None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 바이러스", Ability Icon String(Hero(솜브라), Button(Ability 1))), Null, Custom String(
			" SHIFT\r\n 바이러스에 걸린 동안 적이 이동할 수 없음                                         "), Left, 6, Color(Green), Color(흰색), Color(흰색),
			None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 5, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 광역해킹", Ability Icon String(Hero(솜브라), Button(Ultimate))), Null, Custom String(
			" Q (라운드 대기 시간에만 사용 가능, 승자결정전에서 사용 불가)\r\n 1. 다음 라운드 셀의 색깔을 해킹하여 모든 플레이어들에게 혼란을 줌\r\n 2. 범위 내의 적들을 5초간 해킹하며 2.5초간 넉다운시킴"),
			Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
	}
}

rule("[솜브라] : 광역해킹 - 넘어뜨리기")
{
	event
	{
		Ongoing - Each Player;
		All;
		솜브라;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Event Player.D = Players Within Radius(Event Player, 15, Opposite Team Of(Team Of(Event Player)), Off);
		Event Player.D = Filtered Array(Event Player.D, Current Array Element != Event Player);
		Set Status(Event Player.D, Event Player, Knocked Down, 2.500);
		disabled Damage(All Players(All Teams), Event Player, 10);
		Small Message(Event Player.D, Custom String("{0} 솜브라 : 어라, 혹시 무슨 일 있었어?", Hero Icon String(Hero(솜브라))));
		Wait(3, Ignore Condition);
	}
}

rule("[솜브라] : 광역해킹 - 색깔 가리기 by KISUM")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Is Using Ultimate(Players On Hero(Hero(솜브라), All Teams)) == True;
	}

	action
	{
		Global.sombra_hide = 1;
		Wait(7, Ignore Condition);
		Global.sombra_hide = 0;
	}
}

rule("[솜브라] : 궁극기 사용 가능 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		솜브라;
	}

	condition
	{
		Match Time > 30;
	}

	action
	{
		Allow Button(Event Player, Button(Ultimate));
	}
}

rule("[솜브라] : 궁극기 사용 불가 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		솜브라;
	}

	condition
	{
		Match Time <= 30;
	}

	action
	{
		Disallow Button(Event Player, Button(Ultimate));
	}
}

rule("[솜브라] : 바이러스 - Rooted by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		솜브라;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Set Status(Victim, Null, Rooted, 0.250);
	}
}

rule("[솜브라] : 색깔확인 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		솜브라;
	}

	condition
	{
		Is Alive(Event Player) == True;
		Is Button Held(Event Player, Button(Reload)) == True;
	}

	action
	{
		If(Global.CorrectColour == 1);
			Small Message(Event Player, Custom String("경기도의 딸 KISUM : 하얀색(WHITE) 셀로 가면 돼!"));
		Else If(Global.CorrectColour == 2);
			Small Message(Event Player, Custom String("경기도의 딸 KISUM : 노란색(YELLOW) 셀로 가면 돼!"));
		Else If(Global.CorrectColour == 3);
			Small Message(Event Player, Custom String("경기도의 딸 KISUM : 초록색(GREEN) 셀로 가면 돼!"));
		Else If(Global.CorrectColour == 4);
			Small Message(Event Player, Custom String("경기도의 딸 KISUM : 보라색(PURPLE) 셀로 가면 돼!"));
		Else If(Global.CorrectColour == 5);
			Small Message(Event Player, Custom String("경기도의 딸 KISUM : 빨간색(RED) 셀로 가면 돼!"));
		Else If(Global.CorrectColour == 6);
			Small Message(Event Player, Custom String("경기도의 딸 KISUM : 파란색(BLUE) 셀로 가면 돼!"));
		Else If(Global.CorrectColour == 7);
			Small Message(Event Player, Custom String("경기도의 딸 KISUM : 주황색(ORANGE) 셀로 가면 돼!"));
		Else If(Global.CorrectColour == 8);
			Small Message(Event Player, Custom String("경기도의 딸 KISUM : 하늘색(AQUA) 셀로 가면 돼!"));
		End;
	}
}

rule("[D.VA] : 능력 설명 + HANA1 by KISUM * (특전관련 수정)")
{
	event
	{
		Ongoing - Each Player;
		All;
		D.Va;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is In Alternate Form(Event Player) == False;
		Event Player.ttek_left_enable != True;
	}

	action
	{
		Create Progress Bar HUD Text(Players On Hero(Hero(D.Va), All Teams), 6.667 * Event Player.HANA1, Custom String("빙글뱅글 남은횟수 : {0}회",
			Event Player.HANA1), Left, 11, Color(Green), Color(흰색), Visible To Values and Color, Visible Never);
		Create HUD Text(Event Player, Custom String("{0}     빙글뱅글", Icon String(Dizzy)), Null, Custom String(
			" 좌클릭 (송하나 상태 시 활성화)\r\n 1. 횟수 제한 O (메카 내린 시점 라운드 수 + 1로 세팅)\r\n 2. 피격 성공 시 적이 2초간 회전하며 횟수 - 1 카운트\r\n 3. 피격 여부 관계 없이 송하나가 1초간 스턴 상태 유지"),
			Left, 10, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 9, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 넉백 미사일", Ability Icon String(Hero(D.Va), Button(Ability 2))), Null, Custom String(
			" E\r\n 마이크로 미사일에 맞은 적에게 넉백효과 부여          "), Left, 8, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}           자폭", Ability Icon String(Hero(D.Va), Button(Ultimate))), Null,
			Custom String(" Q (1회 사용 가능, 메카 재탑승 불가, 미사용시 9라운드에 자동 발동)\r\n 모든 적들을 3.5초간 해킹하며 범위 내 적들에게 강력한 넉백효과 부여"), Left, 4, Color(Green),
			Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}    즉시 회복", Icon String(Plus)), Null, Custom String(
			" 패시브\r\n 적에 의해 궁극기 게이지가 감소되더라도 즉시 회복                  "), Left, 2, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Event Player.DVQ = 2;
	}
}

rule("[D.VA] : 마이크로 미사일 - 넉백 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		D.Va;
	}

	condition
	{
		Is Using Ability 2(Players On Hero(Hero(D.Va), All Teams)) == True;
		Is In Alternate Form(Event Player) == False;
	}

	action
	{
		Abort If Condition Is False;
		Apply Impulse(Victim, Position Of(Victim) - Position Of(Event Player), 10, To World, Cancel Contrary Motion);
	}
}

rule("[D.VA] : 자폭 - 플레이어 해킹 by  KISUM (특전관련 수정)")
{
	event
	{
		Ongoing - Each Player;
		All;
		D.Va;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
		Event Player.Z != 1;
		Event Player.DVQ != 1;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} D.VA : 어서 피하는게 좋을 걸?", Hero Icon String(Hero(D.Va))));
		Set Status(Filtered Array(All Players(All Teams), Current Array Element != Event Player), Null, Hacked, 3.500);
		Set Ultimate Ability Enabled(Event Player, False);
		Disallow Button(Event Player, Button(Ultimate));
	}
}

rule("[D.VA] : 9라운드 자동 자폭 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		D.Va;
	}

	condition
	{
		Is In Alternate Form(Event Player) == False;
		Global.RoundNumber >= 9;
	}

	action
	{
		Press Button(Event Player, Button(Ultimate));
		Wait(1, Ignore Condition);
		Loop If(Is In Alternate Form(Event Player) == False);
		Big Message(All Players(All Teams), Custom String("{0} D.VA : 내 메카가 고장나다니 ㅜㅜ", Hero Icon String(Hero(D.Va))));
	}
}

rule("[D.VA] : 궁극기 게이지 감소 무시 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		D.Va;
	}

	condition
	{
		Ultimate Charge Percent(Event Player) > 0;
		Ultimate Charge Percent(Event Player) < 100;
	}

	action
	{
		Set Ultimate Charge(Event Player, 100);
	}
}

rule("[D.Va] : 빙글뱅글 by KISUM (특전관련 수정)")
{
	event
	{
		Player Took Damage;
		All;
		All;
	}

	condition
	{
		Attacker == Players On Hero(Hero(D.Va), All Teams);
		Attacker.hana_count == 1;
		Attacker.HANA1 > 0;
		Is In Alternate Form(Attacker) == True;
	}

	action
	{
		Attacker.HANA1 = Attacker.HANA1 + -1;
		Small Message(Event Player, Custom String("{0} 송하나 : 니가 아주 미쳐 도는구나?", Hero Icon String(Hero(D.Va))));
		Start Facing(Event Player, Event Player, 3200, To Player, Direction and Turn Rate);
		disabled Start Camera(Event Player, Global.ArenaCentre + Vector(0, -200, 0), Global.ArenaCentre + Vector(0, -500, 0), 0);
		Wait(2, Ignore Condition);
		Stop Facing(Event Player);
		disabled Stop Camera(Event Player);
	}
}

rule("[D.VA] : 송하나 - 좌클릭 허용 by KISUM (특전관련 수정)")
{
	event
	{
		Ongoing - Each Player;
		All;
		D.Va;
	}

	condition
	{
		Is In Alternate Form(Event Player) == True;
		Event Player.DVQ != 1;
		Is Using Ultimate(Event Player) != True;
	}

	action
	{
		Event Player.GD = 3;
		Wait(1, Ignore Condition);
		Disallow Button(Event Player, Button(Ultimate));
		Wait(2.500, Ignore Condition);
		Event Player.HANA1 = 1 + Global.RoundNumber;
		Event Player.hana_count = 1;
		Set Primary Fire Enabled(Event Player, True);
	}
}

rule("[D.VA] : 송하나 - 좌클릭 스턴 by KISUM (특전관련 수정)")
{
	event
	{
		Ongoing - Each Player;
		All;
		D.Va;
	}

	condition
	{
		Is In Alternate Form(Event Player) == True;
		Event Player.hana_count == 1;
		Is Firing Primary(Event Player) == True;
		Event Player.ttek_left_enable == False;
	}

	action
	{
		Set Status(Event Player, Null, Stunned, 1);
	}
}

rule("[D.VA] : 송하나 - 좌클릭 비허용 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		D.Va;
	}

	condition
	{
		Event Player.HANA1 == 0;
	}

	action
	{
		Set Primary Fire Enabled(Event Player, False);
	}
}

rule("[D.VA] : 송하나 - 좌클릭 카운트 by KISUM")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Match Round == 1;
	}

	action
	{
		Global.BLH = Custom String("저칼슘");
		Wait(0.500, Ignore Condition);
		Global.BLH = Custom String("songswing");
		Wait(0.500, Ignore Condition);
		Global.BLH = Custom String("Redboy1076");
		Wait(0.500, Ignore Condition);
		Global.BLH = Custom String("죄와벌");
		Wait(0.500, Ignore Condition);
		Global.BLH = Custom String("URUZ");
		Wait(0.500, Ignore Condition);
		Global.BLH = Custom String("kidfsf");
		Wait(0.500, Ignore Condition);
		Global.BLH = Custom String("갱돌");
		Wait(0.500, Ignore Condition);
		Global.BLH = Custom String("Cool");
		Wait(0.500, Ignore Condition);
		Global.BLH = Custom String("맥크리");
		Wait(0.500, Ignore Condition);
		Global.BLH = Custom String("미친마법사");
		Wait(0.500, Ignore Condition);
		Global.BLH = Custom String("데스나이트");
		Wait(0.500, Ignore Condition);
		Global.BLH = Custom String("초보자");
		Wait(0.500, Ignore Condition);
		Global.BLH = Custom String("엄청난자객");
		Wait(0.500, Ignore Condition);
		Global.BLH = Custom String("Dolphin");
	}
}

rule("[맥크리] : 능력 설명 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		캐서디;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0}        섬광탄", Ability Icon String(Hero(캐서디), Button(Ability 2))), Null,
			Custom String(" E\r\n 1. 사용시 궁극기 게이지 40% 필요\r\n 2. 부착 시 2초 스턴     "), Left, 8, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}        구르기", Ability Icon String(Hero(캐서디), Button(Ability 1))), Null,
			Custom String(" SHIFT\r\n 1. 사용시 궁극기 게이지 20% 필요\r\n 2. 구르는 동안 시간 정지                     "), Left, 4, Color(Green), Color(흰색),
			Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 차가운 석양", Ability Icon String(Hero(캐서디), Button(Ultimate))), Null, Custom String(
			" Q\r\n 0.5초간의 시전 시간 이후 시야 내의 적들을 3초간 빙결시킴        "), Left, 2, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
	}
}

rule("[맥크리] : 석양이 진다 - 얼음")
{
	event
	{
		Ongoing - Each Player;
		All;
		캐서디;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Event Player.M = Players Within Radius(Event Player, 1000, Opposite Team Of(Team Of(Event Player)), Surfaces);
		Event Player.M = Filtered Array(Event Player.M, Current Array Element != Event Player);
		Wait(0.500, Ignore Condition);
		Set Status(Event Player.M, Event Player, Frozen, 3);
		Small Message(Event Player.M, Custom String("{0} 맥크리 : 해가 지니 날씨가 쌀쌀하군.", Hero Icon String(Hero(캐서디))));
	}
}

rule("[맥크리] : 섬광탄 - 스턴 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		캐서디;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Set Status(Victim, Null, Stunned, 2);
		Small Message(Victim, Custom String("{0} 맥크리 : 깜짝 놀랬지?!", Hero Icon String(Hero(캐서디))));
	}
}

rule("[맥크리] : 섬광탄 사용시 궁극기 게이지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		캐서디;
	}

	condition
	{
		Is Using Ability 2(Event Player) == True;
	}

	action
	{
		Set Ultimate Charge(Event Player, Ultimate Charge Percent(Event Player) + -40);
	}
}

rule("[맥크리] : 섬광탄 사용 불가 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		캐서디;
	}

	condition
	{
		Ultimate Charge Percent(Event Player) < 40;
	}

	action
	{
		Set Ability 2 Enabled(Event Player, False);
	}
}

rule("[맥크리] : 섬광탄 사용 가능 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		캐서디;
	}

	condition
	{
		Ultimate Charge Percent(Event Player) >= 40;
	}

	action
	{
		Set Ability 2 Enabled(Event Player, True);
	}
}

rule("[맥크리] : 구르기 사용시 궁극기 게이지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		캐서디;
	}

	condition
	{
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Set Ultimate Charge(Event Player, Ultimate Charge Percent(Event Player) + -20);
		Pause Match Time;
		Wait(0.200, Ignore Condition);
		Unpause Match Time;
	}
}

rule("[맥크리] : 구르기 사용 불가 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		캐서디;
	}

	condition
	{
		Ultimate Charge Percent(Event Player) < 20;
	}

	action
	{
		Set Ability 1 Enabled(Event Player, False);
	}
}

rule("[맥크리] : 구르기 사용 가능 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		캐서디;
	}

	condition
	{
		Ultimate Charge Percent(Event Player) >= 20;
	}

	action
	{
		Set Ability 1 Enabled(Event Player, True);
	}
}

rule("[아나] : 능력 설명 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		아나;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 업고 던지기", Icon String(Trashcan)), Null, Custom String(
			" 좌클릭 (업기) / 우클릭 (던지기)\n 자고 있는 적을 업은 후 던짐 (적군 점프로 탈출 가능 주의)             "), Left, 8, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		disabled Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		disabled Create HUD Text(Event Player, Custom String("{0} 수면 수류탄", Ability Icon String(Hero(아나), Button(Ability 2))), Null, Custom String(
			" E\r\n 수류탄에 맞은 적들에게 3초간 수면상태 부여                              "), Left, 6, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 5, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 나노 강화제", Ability Icon String(Hero(아나), Button(Ultimate))), Null, Custom String(
			" Q (에임 필요)\r\n 1. 조준선에 가장 가까운 적에게 5초간 수면상태 부여\r\n 2. 모든 적들에게 1.5초간 수면상태 부여 (10라운드까지만 발동)     "), Left, 4, Color(Green), Color(
			흰색), Color(흰색), None, Visible Never);
	}
}

disabled rule("[아나] : 생체 수류탄 - 수면 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		아나;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Is Using Ability 2(Event Player) == True;
	}

	action
	{
		Set Status(Victim, Null, Asleep, 3);
		Small Message(Victim, Custom String("{0} 아나 : 잠깐 눈 좀 붙여", Hero Icon String(Hero(아나))));
	}
}

rule("[아나] : 나노 강화제 - 수면 10라운드 이전 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		아나;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
		Global.RoundNumber <= 10;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 아나 : 쉿, 모두 잘 시간이야.", Hero Icon String(Hero(아나))));
		Damage(Filtered Array(All Players(All Teams), Current Array Element != Event Player), Event Player, 100);
		Set Status(Filtered Array(All Players(All Teams), Current Array Element != Event Player), Event Player, Asleep, 1.500);
	}
}

rule("[아나] : 나노 강화제 - 수면 with KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		아나;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Wait(0.100, Ignore Condition);
		Small Message(Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams)
			!= Is Dead(Player Closest To Reticle(Event Player, All Teams))), Custom String("{0} 아나 : 쉿, 넌 특별히 더 오래 재워줄게.",
			Hero Icon String(Hero(아나))));
		Damage(Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams)
			!= Is Dead(Player Closest To Reticle(Event Player, All Teams))), Event Player, 100);
		Set Status(Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams)
			!= Is Dead(Player Closest To Reticle(Event Player, All Teams))), Event Player, Hacked, 0.100);
		Set Status(Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams)
			!= Is Dead(Player Closest To Reticle(Event Player, All Teams))), Event Player, Asleep, 4.900);
	}
}

rule("[아나] : 주변에 자는 적 존재 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Entity Exists(First Of(Sorted Array(Filtered Array(All Players(All Teams), Has Status(Current Array Element, Asleep)
			== True && Current Array Element != Event Player && Distance Between(Event Player, Current Array Element)
			<= 3 && Entity Exists(Current Array Element.thrower) == False && Is On Ground(Current Array Element) == True),
			Distance Between(Event Player, Current Array Element)))) == True;
	}

	action
	{
		Event Player.closeToPlayer = True;
	}
}

rule("[아나] : 적군 업기 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		아나;
	}

	condition
	{
		Is Button Held(Event Player, Button(Primary Fire)) == True;
		Entity Exists(Event Player.playerCarried) == False;
		Event Player.closeToPlayer == True;
		Has Status(Event Player, Knocked Down) == False;
		Has Status(Event Player, Asleep) == False;
		Has Status(Event Player, Frozen) == False;
		Has Status(Event Player, Stunned) == False;
	}

	action
	{
		Event Player.playerCarried = First Of(Sorted Array(Filtered Array(All Players(All Teams), Has Status(Current Array Element, Asleep)
			== True && Current Array Element != Event Player), Distance Between(Current Array Element, Event Player)));
		Event Player.playerCarried.thrower = Event Player;
		Attach Players(Event Player.playerCarried, Event Player, Vector(0, 2, 0));
		Play Effect(Event Player, Buff Impact Sound, Color(흰색), Event Player, 200);
		Small Message(Event Player, Custom String("{1} 업기 성공!", Null, Event Player.playerCarried));
		Small Message(Event Player.playerCarried, Custom String("점프를 눌러 탈출할 수 있어요!"));
		Wait(0.250, Ignore Condition);
	}
}

rule("[아나] : 주변에 자는 적 없음 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Entity Exists(First Of(Sorted Array(Filtered Array(All Players(All Teams), Has Status(Current Array Element, Asleep)
			== True && Current Array Element != Event Player && Distance Between(Event Player, Current Array Element)
			<= 3 && Entity Exists(Current Array Element.thrower) == False && Is On Ground(Current Array Element) == True),
			Distance Between(Event Player, Current Array Element)))) == False;
	}

	action
	{
		Event Player.closeToPlayer = False;
	}
}

rule("[아나] : 적군 던지기 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		아나;
	}

	condition
	{
		Is Button Held(Event Player, Button(Secondary Fire)) == True;
		Entity Exists(Event Player.playerCarried) == True;
		Has Status(Event Player, Knocked Down) == False;
		Has Status(Event Player, Asleep) == False;
		Has Status(Event Player, Frozen) == False;
		Has Status(Event Player, Stunned) == False;
	}

	action
	{
		Detach Players(Event Player.playerCarried);
		Apply Impulse(Event Player.playerCarried, Vector(X Component Of(Facing Direction Of(Event Player)), -0.100, Z Component Of(
			Facing Direction Of(Event Player))), 50, To World, Cancel Contrary Motion);
		Damage(Event Player.playerCarried, Event Player, 100);
		Event Player.playerCarried = Null;
	}
}

rule("[아나] : 업힌 적군 탈출 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Entity Exists(Event Player.thrower.playerCarried) == True;
		Is Button Held(Event Player, Button(Jump)) == True;
		Event Player.thrower.playerCarried == Event Player;
		Has Status(Event Player, Knocked Down) == False;
		Has Status(Event Player, Asleep) == False;
		Has Status(Event Player, Frozen) == False;
		Has Status(Event Player, Stunned) == False;
		Has Status(Event Player, Rooted) == False;
	}

	action
	{
		Detach Players(Event Player);
		Small Message(Event Player.thrower, Custom String("{0} : 넌 날 가질 수 없어!", Event Player));
		Event Player.thrower.playerCarried = Null;
		If(Is Dummy Bot(Event Player.thrower) == True);
			Event Player.thrower.isChasing = False;
		End;
		Event Player.thrower = Null;
	}
}

rule("[아나] : 아나 상태 이상 시 업은 적군 놓치기 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		아나;
	}

	condition
	{
		(Has Status(Event Player, Knocked Down) || Has Status(Event Player, Asleep) || Has Status(Event Player, Frozen) || Has Status(
			Event Player, Stunned)) == True;
		Entity Exists(Event Player.playerCarried) == True;
	}

	action
	{
		Detach Players(Sorted Array(Filtered Array(All Players(All Teams), Distance Between(Position Of(Event Player) + Vector(0, 2, 0),
			Position Of(Current Array Element)) <= 0.500), Distance Between(Position Of(Event Player) + Vector(0, 2, 0), Position Of(
			Current Array Element))));
		Detach Players(Sorted Array(Filtered Array(All Players(All Teams), Distance Between(Position Of(Event Player) + Vector(0, 4, 0),
			Position Of(Current Array Element)) <= 0.500), Distance Between(Position Of(Event Player) + Vector(0, 4, 0), Position Of(
			Current Array Element))));
		Small Message(Event Player, Custom String("이런 놓쳐버리다니..."));
		Event Player.playerCarried = Null;
	}
}

rule("[아나] : 던지거나 탈출하거나 놓친 적군 자유 모드 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		disabled Is On Ground(Event Player) == True;
		Event Player.thrower.playerCarried == Null;
	}

	action
	{
		Wait(0.500, Abort When False);
		Event Player.thrower = Null;
		Detach Players(Event Player);
	}
}

rule("[모이라] : 능력 설명 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		모이라;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 시간 소멸", Ability Icon String(Hero(모이라), Button(Ability 1))), Null, Custom String(
			" SHIFT\r\n 소멸과 동시에 라운드 시간을 반으로 감소시킴"), Left, 6, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 5, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 도트 빙결", Ability Icon String(Hero(메이), Button(Ability 1))), Null, Custom String(
			" 패시브\r\n 공격에 맞은 적을 도트 빙결시킴                    "), Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
	}
}

rule("[모이라] : 생체구슬 - 도트 빙결")
{
	event
	{
		Player Dealt Damage;
		All;
		모이라;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Is Using Ability 1(Event Player) == False;
	}

	action
	{
		Set Status(Victim, Null, Frozen, 0.150);
	}
}

rule("[모이라] : 시간 소멸 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		모이라;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Event Player.Z != 1;
		Is Using Ability 1(Event Player) == True;
		Match Time <= 20;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 모이라 : 시간이 반밖에 안 남은 것 같은데?", Hero Icon String(Hero(모이라))));
		Set Match Time(Match Time / 2);
		Wait(0.100, Ignore Condition);
		Damage(All Living Players(All Teams), Event Player, 100);
	}
}

rule("[위도우메이커] : 능력설명 with KISUM *")
{
	event
	{
		Ongoing - Each Player;
		All;
		위도우메이커;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 저격", Ability Icon String(Hero(위도우메이커), Button(Primary Fire))), Null,
			Custom String(" 우클릭\r\n 공격에 맞은 적을 0.5초간 빙결시킴"), Left, 8, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}         거미", Ability Icon String(Hero(위도우메이커), Button(Ability 2))), Null,
			Custom String(" SHIFT\r\n 거미를 밟은 적의 몸에 독을 퍼트려 도트 빙결시킴"), Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}         각성", Hero Icon String(Hero(위도우메이커))), Null, Custom String(
			" 패시브\r\n 1. 5라운드부터 공격에 맞은 적의 빙결시간이 2배로 증가\r\n 2. 9라운드부터 공격에 맞은 적의 빙결시간이 3배로 증가"), Left, 2, Color(Green), Color(흰색), Color(흰색),
			None, Visible Never);
	}
}

rule("[위도우메이커] : 저격총 - 얼음")
{
	event
	{
		Player Dealt Damage;
		All;
		위도우메이커;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Global.RoundNumber < 5;
	}

	action
	{
		Set Status(Victim, Null, Frozen, 0.500);
	}
}

rule("[위도우메이커] : 패시브 - 각성 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		위도우메이커;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Global.RoundNumber >= 5;
		Global.RoundNumber < 9;
	}

	action
	{
		Set Status(Victim, Null, Frozen, 1);
	}
}

rule("[위도우메이커] : 패시브 - 각성 알림 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		위도우메이커;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Global.RoundNumber == 5;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 위도우메이커 : 드디어 각성할 시간이군.", Hero Icon String(Hero(위도우메이커))));
	}
}

rule("[위도우메이커] : 패시브 - 초각성 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		위도우메이커;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Global.RoundNumber >= 9;
	}

	action
	{
		Set Status(Victim, Null, Frozen, 1.500);
	}
}

rule("[위도우메이커] : 패시브 - 초각성 알림 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		위도우메이커;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Global.RoundNumber == 9;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 위도우메이커 : 좀 더 세게해줄까? 이번엔 초각성이야.", Hero Icon String(Hero(위도우메이커))));
	}
}

rule("[자리야] : 능력설명 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		자리야;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 짭탄", Ability Icon String(Hero(자리야), Button(Ability 2))), Custom String(
			" 남은 쿨타임 {0}초", Event Player.ZRC), Custom String(
			" E (에임필요, 각각의 적에게 단 한번 사용가능)\n 조준선에서 가장 가까운 적을 3초간 움직일 수 없게 함                 "), Left, 6, Color(Green), Color(Yellow), Color(
			흰색), String, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 5, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 무적", Ability Icon String(Hero(자리야), Button(Ability 1))), Null, Custom String(
			" SHIFT\r\n 2초간 무적상태가 되며 적을 통과할 수 있음                        "), Left, 4, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Right, 2.500, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 잔여짭탄", Ability Icon String(Hero(자리야), Button(Ability 2))), Null, Null, Right, 2,
			Color(Red), Color(흰색), Color(흰색), None, Visible Never);
		Event Player.ZRC = 0;
	}
}

rule("[자리야] : 보호방벽 - 무적 + 통과")
{
	event
	{
		Ongoing - Each Player;
		All;
		자리야;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Set Status(Event Player, Null, Phased Out, 2);
	}
}

rule("[자리야] : 짭탄 ZRV 발동 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		자리야;
	}

	condition
	{
		Is Alive(Event Player) == True;
		Event Player.Z != 1;
		Event Player.ZRC == 0;
		Is Button Held(Event Player, Button(Ability 2)) == True;
		Has Status(Event Player, Hacked) == False;
		Has Status(Event Player, Knocked Down) == False;
		Has Status(Event Player, Asleep) == False;
		Has Status(Event Player, Frozen) == False;
		Has Status(Event Player, Stunned) == False;
		Is In View Angle(Event Player, Player Closest To Reticle(Event Player, All Teams), 90) == True;
	}

	action
	{
		If(Current Game Mode == Game Mode(데스매치));
			Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams) != Is Dead(
				Player Closest To Reticle(Event Player, All Teams))).ZRV = 1;
		Else;
			If(Team Of(Event Player) != Team Of(Player Closest To Reticle(Event Player, All Teams)));
				Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams) != Is Dead(
					Player Closest To Reticle(Event Player, All Teams))).ZRV = 1;
	}
}

rule("[자리야] : 짭탄 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Event Player.ZRV == 1;
	}

	action
	{
		Players On Hero(Hero(자리야), All Teams).ZRC = 5;
		Damage(Event Player, Players On Hero(Hero(자리야), All Teams), 100);
		Set Status(Event Player, Players On Hero(Hero(자리야), All Teams), Rooted, 3);
		Small Message(Event Player, Custom String("{0} 자리야 : 짭탄 맛이 어때?", Hero Icon String(Hero(자리야))));
		Create Effect(Filtered Array(All Players(All Teams), Current Array Element != Position Of(Event Player)), Orb, Color(Blue),
			Event Player, 60, Visible To Position and Radius);
		Event Player.ZR1 = Last Created Entity;
		Create Effect(Filtered Array(All Players(All Teams), Current Array Element != Position Of(Event Player)), Sphere, Color(흰색),
			Event Player, 1.800, Visible To Position and Radius);
		Event Player.ZR2 = Last Created Entity;
		Create Effect(Filtered Array(All Players(All Teams), Current Array Element != Position Of(Event Player)), Bad Aura, Color(Purple),
			Event Player, 1.800, Visible To Position and Radius);
		Event Player.ZR3 = Last Created Entity;
		Create Effect(Filtered Array(All Players(All Teams), Current Array Element != Position Of(Event Player)), Sphere, Color(Sky Blue),
			Event Player, 1.700, Visible To Position and Radius);
		Event Player.ZR4 = Last Created Entity;
		Destroy HUD Text(Event Player.Z_GAGE_H);
		Wait(1, Ignore Condition);
		Players On Hero(Hero(자리야), All Teams).ZRC = 4;
		Wait(1, Ignore Condition);
		Players On Hero(Hero(자리야), All Teams).ZRC = 3;
		Wait(1, Ignore Condition);
		Players On Hero(Hero(자리야), All Teams).ZRC = 2;
		Destroy Effect(Event Player.ZR1);
		Destroy Effect(Event Player.ZR2);
		Destroy Effect(Event Player.ZR3);
		Destroy Effect(Event Player.ZR4);
		Wait(1, Ignore Condition);
		Players On Hero(Hero(자리야), All Teams).ZRC = 1;
		Wait(1, Ignore Condition);
		Players On Hero(Hero(자리야), All Teams).ZRC = 0;
	}
}

rule("[자리야] : 사망시 짭탄 삭제 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Is Dead(Event Player) == True;
	}

	action
	{
		Destroy Effect(Event Player.ZR1);
		Destroy Effect(Event Player.ZR2);
		Destroy Effect(Event Player.ZR3);
		Destroy Effect(Event Player.ZR4);
	}
}

rule("[자리야] : 짭탄 - 횟수 표시 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		If(Current Game Mode == Game Mode(데스매치));
			Create HUD Text(Players On Hero(Hero(자리야), All Teams), Custom String("{0} 사용가능", Hero Icon String(Hero Of(Event Player)),
				Ability Icon String(Hero(자리야), Button(Ability 2))), Null, Null, Right, 3, Color(흰색), Color(흰색), Color(Red),
				Visible To and String, Default Visibility);
			Event Player.Z_GAGE_H = Last Text ID;
		Else;
			If(Team Of(Event Player) != Team Of(Players On Hero(Hero(자리야), All Teams)));
				Create HUD Text(Players On Hero(Hero(자리야), All Teams), Custom String("{0} 사용가능", Hero Icon String(Hero Of(Event Player)),
					Ability Icon String(Hero(자리야), Button(Ability 2))), Null, Null, Right, 3, Color(흰색), Color(흰색), Color(Red),
					Visible To and String, Default Visibility);
				Event Player.Z_GAGE_H = Last Text ID;
	}
}

rule("[자리야] : 짭탄 - 횟수 표시 삭제 1 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Is Alive(Event Player) == False;
	}

	action
	{
		Destroy HUD Text(Event Player.Z_GAGE_H);
	}
}

rule("[자리야] : 짭탄 - 횟수 표시 삭제 2 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Event Player == Players On Hero(Hero(자리야), All Teams);
	}

	action
	{
		Destroy HUD Text(Event Player.Z_GAGE_H);
	}
}

rule("[시메트라] : 능력 설명 by KISUM *")
{
	event
	{
		Ongoing - Each Player;
		All;
		시메트라;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 버블버블", Icon String(Ring Thick)), Null, Custom String(
			" 우클릭\n 버블에 맞은 적에게 0.25초간 빙결상태 부여                          "), Left, 10, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 9, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 순간이동기", Ability Icon String(Hero(시메트라), Button(Ability 2))), Null, Custom String(
			" E\r\n 사용시 궁극기 게이지 60% 필요                                      "), Left, 8, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 감시 포탑", Ability Icon String(Hero(시메트라), Button(Ability 1))), Null, Custom String(
			" SHIFT\r (최소한의 사용 텀 존재)\n 사용시 궁극기 게이지 20% 필요                                          "), Left, 4, Color(Green), Color(흰색),
			Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 광자 방벽", Ability Icon String(Hero(시메트라), Button(Ultimate))), Null, Custom String(
			" Q (라운드시간 내에서만 사용 가능, 패자부활전에서 사용 불가)\r\n 라운드시간을 7초로 조정한 후 모든 적 4초간 스턴상태 부여\r\n 단, 승자결정전에서 사용시 효과 없음"), Left, 2, Color(Green),
			Color(흰색), Color(흰색), None, Visible Never);
	}
}

rule("[시메트라] : 순간이동기 사용시 궁극기 게이지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		시메트라;
	}

	condition
	{
		Is Using Ability 2(Event Player) == True;
	}

	action
	{
		Set Ultimate Charge(Event Player, Ultimate Charge Percent(Event Player) + -60);
	}
}

rule("[시메트라] : 순간이동기 사용 불가 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		시메트라;
	}

	condition
	{
		Ultimate Charge Percent(Event Player) < 60;
	}

	action
	{
		Set Ability 2 Enabled(Event Player, False);
	}
}

rule("[시메트라] : 순간이동기 사용 가능 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		시메트라;
	}

	condition
	{
		Ultimate Charge Percent(Event Player) >= 60;
	}

	action
	{
		Set Ability 2 Enabled(Event Player, True);
	}
}

rule("[시메트라] : 감시포탑 사용시 궁극기 게이지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		시메트라;
	}

	condition
	{
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Set Ultimate Charge(Event Player, Ultimate Charge Percent(Event Player) + -20);
		Set Ability 1 Enabled(Event Player, False);
		Wait(0.750, Ignore Condition);
		If(Ultimate Charge Percent(Event Player) >= 20);
			Set Ability 1 Enabled(Event Player, True);
	}
}

rule("[시메트라] : 감시포탑 사용 불가 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		시메트라;
	}

	condition
	{
		Ultimate Charge Percent(Event Player) < 20;
	}

	action
	{
		Set Ability 1 Enabled(Event Player, False);
	}
}

rule("[시메트라] : 감시포탑 사용 가능 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		시메트라;
	}

	condition
	{
		Ultimate Charge Percent(Event Player) >= 20;
	}

	action
	{
		Set Ability 1 Enabled(Event Player, True);
	}
}

rule("[시메트라] : 광자 방벽 - 스턴 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		시메트라;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
		Global.RoundNumber != 420.690;
		Global.consolation_on != 1;
		Match Time <= 30;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 시메트라 : 이 여왕님의 워킹을 감상하도록!", Hero Icon String(Hero(시메트라))));
		Set Match Time(7);
		Small Message(Filtered Array(All Players(All Teams), Current Array Element != Event Player), Custom String(
			"{0} 시메트라 : 조금만 기다리면 움직이게 해줄게^^", Hero Icon String(Hero(시메트라))));
		Set Status(Filtered Array(All Players(All Teams), Current Array Element != Event Player), Null, Stunned, 4);
		Wait(3.500, Ignore Condition);
		Small Message(Filtered Array(All Players(All Teams), Current Array Element != Event Player), Custom String(
			"{0} 시메트라 : 이제 움직여도 좋아~", Hero Icon String(Hero(시메트라))));
	}
}

rule("[시메트라] : 광자방벽 사용 불가 1 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		시메트라;
	}

	condition
	{
		Match Time > 30;
	}

	action
	{
		Disallow Button(Event Player, Button(Ultimate));
	}
}

rule("[시메트라] : 광자방벽 사용 불가 2 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		시메트라;
	}

	condition
	{
		Global.consolation_on == 1;
	}

	action
	{
		Disallow Button(Event Player, Button(Ultimate));
	}
}

rule("[시메트라] : 광자방벽 사용 가능 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		시메트라;
	}

	condition
	{
		Match Time <= 30;
		Global.consolation_on != 1;
	}

	action
	{
		Allow Button(Event Player, Button(Ultimate));
	}
}

rule("[시메트라] : 버블버블 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		시메트라;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Set Status(Victim, Null, Frozen, 0.250);
	}
}

rule("[브리기테] : 능력 설명 by KISUM *")
{
	event
	{
		Ongoing - Each Player;
		All;
		브리기테;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 핫팩", Icon String(Fire)), Null, Custom String(
			" E (궁극기가 사용되는 동안 사용 가능, 에임 필요)\r\n 조준선에서 가장 가까운 적에게 6초간 화상상태 부여              "), Left, 6, Color(Green), Color(흰색), Color(흰색),
			None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 5, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 집결", Ability Icon String(Hero(브리기테), Button(Ultimate))), Null, Custom String(
			" Q\r\n 1. 라운드 시간을 10초로 조정한 후 모든 적들을 나에게 집결시킴\r\n 2. 이후 모든 적들에게 2초간 스턴상태 부여                                              "),
			Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
	}
}

rule("[브리기테] : 집결 - 텔레포트 및 스턴 (신버전) by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		브리기테;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
		Global.RoundNumber != 420.690;
		Match Time <= 30;
	}

	action
	{
		Set Match Time(10);
		Big Message(All Players(All Teams), Custom String("{0} 브리기테 : 모두 나에게 집결하라!", Hero Icon String(Hero(브리기테))));
		Teleport(Filtered Array(All Living Players(All Teams), Event Player.Z != 1), Position Of(Event Player) + Vector(0, 0.750, 0));
		Set Status(Filtered Array(All Players(All Teams), Current Array Element != Event Player), Event Player, Stunned, 2);
	}
}

rule("[브리기테] : 핫팩 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		브리기테;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
		Is Button Held(Event Player, Button(Ability 2)) == True;
		Ability Charge(Event Player, Button(Ability 2)) > 0;
	}

	action
	{
		Set Ability Charge(Event Player, Button(Ability 2), Ability Charge(Event Player, Button(Ability 2)) + -1);
		Set Status(Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams)
			!= Is Dead(Player Closest To Reticle(Event Player, All Teams))), Event Player, Burning, 6);
		Small Message(Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams)
			!= Is Dead(Player Closest To Reticle(Event Player, All Teams))), Custom String("{0} 브리기테 : 내 핫팩 받아줘!", Hero Icon String(Hero(
			브리기테))));
	}
}

rule("[오리사] : 능력 설명 by KISUM *")
{
	event
	{
		Ongoing - Each Player;
		All;
		오리사;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 방어 강화", Ability Icon String(Hero(오리사), Button(Ability 1))), Null, Custom String(
			" SHIFT (에임필요)\r\n 조준선에서 가장 가까운 적에게 해킹상태 부여\r\n (라운드가 거듭될수록 해킹상태 시간이 길어짐)                         "), Left, 3, Color(Green),
			Color(흰색), Color(흰색), None, Visible Never);
	}
}

rule("[오리사] : 방어 강화 - 해킹 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		오리사;
	}

	condition
	{
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Set Status(Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams)
			!= Is Dead(Player Closest To Reticle(Event Player, All Teams))), Event Player, Hacked, Global.RoundNumber);
		Small Message(Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams)
			!= Is Dead(Player Closest To Reticle(Event Player, All Teams))), Custom String("{0} 오리사 : 어디 아프십니까?", Hero Icon String(Hero(
			오리사))));
	}
}

rule("[바티스트] : 능력 설명 by KISUM *")
{
	event
	{
		Ongoing - Each Player;
		All;
		바티스트;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 불사 장치", Ability Icon String(Hero(바티스트), Button(Ability 2))), Null, Custom String(
			" E\r (셀 대체 가능)\n 불사 장치에 들어가 있으면 죽지 않음                                        "), Left, 6, Color(Green), Color(흰색), Color(흰색),
			None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 5, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}     슬로우", Icon String(Arrow: Down)), Null, Custom String(
			" SHIFT (에임필요)\r\n 조준선에서 가장 가까운 적의 스킬을 끊고, 7초간 이동속도를 감소시킴"), Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3.500, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}  세일러문", Icon String(Flag)), Null, Custom String(
			" Q (에임필요, 총 게이지 1000, 자연 감소 초당 -4)                    \r\n 1. 본인 및 아군 통과 정답셀로 이동 -100\r\n 2. 적군 통과 랜덤셀로 이동 -20"), Left, 3,
			Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Global.door_count = 1000;
	}
}

rule("[바티스트] : 슬로우 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		바티스트;
	}

	condition
	{
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Set Status(Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams)
			!= Is Dead(Player Closest To Reticle(Event Player, All Teams))), Event Player, Burning, 6.800);
		Set Status(Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams)
			!= Is Dead(Player Closest To Reticle(Event Player, All Teams))), Event Player, Hacked, 0.100);
		Damage(Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams)
			!= Is Dead(Player Closest To Reticle(Event Player, All Teams))), Event Player, 100);
		Small Message(Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams)
			!= Is Dead(Player Closest To Reticle(Event Player, All Teams))), Custom String("{0} 바티스트 : 그렇게 느려서 이길 수 있겠어?",
			Hero Icon String(Hero(바티스트))));
	}
}

rule("[바티스트] : 세일러문 생성 by Dote6 (특전으로 인해, 남은 게이지 보여주는게 위치도 갱신하도록 수정 by Dote6)")
{
	event
	{
		Ongoing - Each Player;
		All;
		바티스트;
	}

	condition
	{
		Ultimate Charge Percent(Event Player) == 100;
		Is Button Held(Event Player, Button(Ultimate)) == True;
		Is Alive(Event Player) == True;
		Has Status(Event Player, Hacked) == False;
		Has Status(Event Player, Knocked Down) == False;
		Has Status(Event Player, Asleep) == False;
		Has Status(Event Player, Frozen) == False;
		Has Status(Event Player, Stunned) == False;
	}

	action
	{
		Set Ultimate Charge(Event Player, 0);
		Set Ultimate Ability Enabled(Event Player, False);
		Set Status(Event Player, Null, Hacked, 0.010);
		Event Player.aim_vector_ = Ray Cast Hit Position(Eye Position(Event Player), Eye Position(Event Player) + Facing Direction Of(
			Event Player) * 100, Null, Event Player, False);
		Event Player.klm_ = Event Player.aim_vector_ - Position Of(Event Player);
		Event Player.unit_vector_ = Vector(1, 0, X Component Of(Event Player.klm_) * -1 / Z Component Of(Event Player.klm_));
		Event Player.unit_vector_ = Normalize(Event Player.unit_vector_);
		Event Player.left_end_ = Event Player.aim_vector_ + Event Player.unit_vector_ * 4;
		Event Player.right_end_ = Event Player.aim_vector_ + Event Player.unit_vector_ * -4;
		Create Beam Effect(All Players(All Teams), Good Beam, Event Player.left_end_, Event Player.left_end_ + Vector(0, 4, 0), Color(
			Yellow), Visible To Position and Radius);
		Wait(0.016, Ignore Condition);
		Global.GD_playerarray = Last Created Entity;
		Create Beam Effect(All Players(All Teams), Good Beam, Event Player.right_end_, Event Player.right_end_ + Vector(0, 4, 0), Color(
			Yellow), Visible To Position and Radius);
		Wait(0.016, Ignore Condition);
		Global.door_effect2 = Last Created Entity;
		Create Beam Effect(All Players(All Teams), Good Beam, Event Player.left_end_, Event Player.right_end_, Color(Yellow),
			Visible To Position and Radius);
		Wait(0.016, Ignore Condition);
		Global.door_effect3 = Last Created Entity;
		Create Beam Effect(All Players(All Teams), Good Beam, Event Player.left_end_ + Vector(0, 4, 0), Event Player.right_end_ + Vector(0,
			4, 0), Color(Yellow), Visible To Position and Radius);
		Wait(0.016, Ignore Condition);
		Global.door_effect4 = Last Created Entity;
		Wait(0.016, Ignore Condition);
		Create In-World Text(All Players(All Teams), Custom String("{0} Sailor Moon {0}", Icon String(Heart)),
			Event Player.aim_vector_ + Vector(0, 4.500, 0), 2, Clip Against Surfaces, Visible To Position and String, Color(Rose),
			Default Visibility);
		Wait(0.016, Ignore Condition);
		Global.door_effect5 = Last Text ID;
		Create Effect(All Players(All Teams), Sparkles, Color(Yellow), Event Player.aim_vector_ + Vector(0, 2, 0), 2,
			Visible To Position and Radius);
		Wait(0.016, Ignore Condition);
		Global.door_effect6 = Last Created Entity;
		Create In-World Text(All Players(All Teams), Custom String("남은 게이지 : {0}", Global.door_count), Event Player.aim_vector_ + Vector(0,
			4.200, 0), 1, Clip Against Surfaces, Visible To Position and String, Color(흰색), Default Visibility);
		Wait(0.016, Ignore Condition);
		Global.door_count_effect = Last Text ID;
		Big Message(All Players(All Teams), Custom String("{0} 바티스트: 세일러문!", Hero Icon String(Hero(바티스트))));
		Global.S = 1;
		Global.bati_theta = Arccosine In Degrees((X Component Of(Event Player.left_end_) - X Component Of(Event Player.aim_vector_)) / 4);
		Skip If(Absolute Value(Sine From Degrees(Global.bati_theta) - (Z Component Of(Event Player.left_end_) - Z Component Of(
			Event Player.aim_vector_)) / 4) < 0.100, 1);
		Global.bati_theta = 360 - Global.bati_theta;
		Chase Global Variable At Rate(bati_theta, 100000000, 60, None);
		While(True);
			Event Player.left_end_ = Event Player.aim_vector_ + 4 * Vector(Cosine From Degrees(Global.bati_theta), 0, Sine From Degrees(
				Global.bati_theta));
			Event Player.right_end_ = Event Player.aim_vector_ + 4 * Vector(Cosine From Degrees(Global.bati_theta + 180), 0, Sine From Degrees(
				Global.bati_theta + 180));
			Wait(0.030, Ignore Condition);
			Continue;
	}
}

rule("[바티스트] : 세일러문 게이지 감소 by KISUM")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.S == 1;
	}

	action
	{
		Global.door_count += -2;
		Wait(0.500, Ignore Condition);
		Loop If(Global.door_count > 0);
	}
}

rule("[바티스트] : 세일러문 trigger by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Global.door_count > 0;
		Angle Between Vectors(Players On Hero(Hero(바티스트), All Teams).left_end_ - Vector(X Component Of(Position Of(Event Player)),
			Y Component Of(Players On Hero(Hero(바티스트), All Teams).aim_vector_), Z Component Of(Position Of(Event Player))),
			Players On Hero(Hero(바티스트), All Teams).right_end_ - Vector(X Component Of(Position Of(Event Player)), Y Component Of(
			Players On Hero(Hero(바티스트), All Teams).aim_vector_), Z Component Of(Position Of(Event Player)))) >= 165;
		Y Component Of(Position Of(Event Player)) - Y Component Of(Players On Hero(Hero(바티스트), All Teams).aim_vector_) <= 4;
		Y Component Of(Position Of(Event Player)) - Y Component Of(Players On Hero(Hero(바티스트), All Teams).aim_vector_) >= -1;
	}

	action
	{
		Start Rule(BATI_TEL_TRIGGER, Restart Rule);
	}
}

rule("[바티스트] : 세일러문 통과 by Dote6")
{
	event
	{
		Subroutine;
		BATI_TEL_TRIGGER;
	}

	action
	{
		Event Player.random_cell = Random Integer(0, 5);
		If(Current Game Mode == Game Mode(데스매치));
			If(Hero Of(Event Player) == Hero(바티스트));
				If(Global.Colours[Event Player.random_cell] != Global.CorrectColour);
					Wait(0.016, Ignore Condition);
					Loop;
				End;
				Global.door_count += -80;
			End;
		Else;
			If(Team Of(Event Player) == Team Of(Players On Hero(Hero(바티스트), All Teams)));
				If(Global.Colours[Event Player.random_cell] != Global.CorrectColour);
					Wait(0.016, Ignore Condition);
					Loop;
				End;
				Global.door_count += -80;
			End;
		End;
		Event Player.random_vector = Global.SphereLocations[Event Player.random_cell] + Vector(0, 0.500, 0);
		Play Effect(All Players(All Teams), Buff Impact Sound, Color(흰색), Event Player, 100);
		Teleport(Event Player, Event Player.random_vector);
		Play Effect(All Players(All Teams), Good Explosion, Color(Yellow), Event Player, 3);
		Small Message(Event Player, Custom String("♥ 세일러문!"));
		Global.door_count += -20;
		Wait(0.016, Ignore Condition);
		If(Current Game Mode == Game Mode(데스매치));
			If(Hero Of(Event Player) != Hero(바티스트));
				Damage(Event Player, Players On Hero(Hero(바티스트), All Teams), 100);
			End;
		Else;
			If(Team Of(Event Player) != Team Of(Players On Hero(Hero(바티스트), All Teams)));
				Damage(Event Player, Players On Hero(Hero(바티스트), All Teams), 100);
			End;
		End;
	}
}

rule("[바티스트] : 세일러문 파괴 by Dote6")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.door_count <= 0;
	}

	action
	{
		Players On Hero(Hero(바티스트), All Teams).left_end = Null;
		Destroy Effect(Global.GD_playerarray);
		Destroy Effect(Global.door_effect2);
		Destroy Effect(Global.door_effect3);
		Destroy Effect(Global.door_effect4);
		Destroy In-World Text(Global.door_effect5);
		Destroy Effect(Global.door_effect6);
		Destroy In-World Text(Global.door_count_effect);
		Play Effect(All Players(All Teams), Bad Explosion, Color(흰색), Players On Hero(Hero(바티스트), All Teams).aim_vector + Vector(0, 2, 0),
			5);
		Big Message(All Players(All Teams), Custom String("{0} {1}: 세일러문이 사라지다니...", Hero Icon String(Hero(바티스트)), Hero(바티스트)));
		Play Effect(All Players(All Teams), Explosion Sound, Color(흰색), Players On Hero(Hero(바티스트), All Teams).aim_vector, 100);
	}
}

rule("[바티스트] : 세일러문 승자결정전 이펙트 by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		바티스트;
	}

	condition
	{
		Global.RoundNumber > 20;
		Global.door_count > 0;
	}

	action
	{
		Global.door_count = 0;
		disabled Create Beam Effect(All Players(All Teams), Good Beam, Event Player.left_end_, Event Player.left_end_ + Vector(0, 4, 0), Color(
			Yellow), Visible To Position and Radius);
		disabled Wait(0.016, Ignore Condition);
		disabled Global.GD_playerarray = Last Created Entity;
		disabled Create Beam Effect(All Players(All Teams), Good Beam, Event Player.right_end_, Event Player.right_end_ + Vector(0, 4, 0), Color(
			Yellow), Visible To Position and Radius);
		disabled Wait(0.016, Ignore Condition);
		disabled Global.door_effect2 = Last Created Entity;
		disabled Create Beam Effect(All Players(All Teams), Good Beam, Event Player.left_end_, Event Player.right_end_, Color(Yellow),
			Visible To Position and Radius);
		disabled Wait(0.016, Ignore Condition);
		disabled Global.door_effect3 = Last Created Entity;
		disabled Create Beam Effect(All Players(All Teams), Good Beam, Event Player.left_end_ + Vector(0, 4, 0), Event Player.right_end_ + Vector(0,
			4, 0), Color(Yellow), Visible To Position and Radius);
		disabled Wait(0.016, Ignore Condition);
		disabled Global.door_effect4 = Last Created Entity;
		disabled Create Effect(All Players(All Teams), Sparkles, Color(Yellow), Event Player.aim_vector_ + Vector(0, 2, 0), 2,
			Visible To Position and Radius);
		disabled Wait(0.016, Ignore Condition);
		disabled Global.door_effect6 = Last Created Entity;
	}
}

rule("[루시우] : 능력 설명 by KISUM *")
{
	event
	{
		Ongoing - Each Player;
		All;
		루시우;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0}        쿨다운", Icon String(Recycle)), Null, Custom String(
			" E\r\n 스킬이 활성화된 동안 소리 파동(우클릭)을 무한으로 사용 가능     "), Left, 8, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 진격의 거인", Ability Icon String(Hero(루시우), Button(Ultimate))), Null, Custom String(
			" Q\r\n 일정시간동안 모든 적들의 크기가 최대 2.4배까지 커짐          "), Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}    이속 증가", Icon String(Arrow: Up)), Null, Custom String(
			" 패시브\r\n 라운드가 거듭될수록 이동속도 증가                        "), Left, 2, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
	}
}

rule("[루시우] : 패시브 - 이동속도 증가 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		루시우;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Match Time == 118;
		Global.RoundNumber <= 20;
	}

	action
	{
		Set Move Speed(Event Player, 111 + Global.RoundNumber * 9);
		Small Message(Event Player, Custom String("{0} 루시우 : 이속 증가!", Hero Icon String(Hero(루시우))));
	}
}

rule("[루시우] : 볼륨을 높여라 설명 - 쿨다운 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		루시우;
	}

	condition
	{
		Is Using Ability 2(Event Player) == True;
	}

	action
	{
		Small Message(Event Player, Custom String("{0} 루시우 : 무한으로 즐겨요~ 소리 파동!", Hero Icon String(Hero(루시우))));
	}
}

rule("[루시우] : 볼륨을 높여라 - 쿨다운 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		루시우;
	}

	condition
	{
		Is Using Ability 2(Event Player) == True;
	}

	action
	{
		Set Ability Cooldown(Event Player, Button(Secondary Fire), 0);
		Wait(0.100, Ignore Condition);
		Loop If Condition Is True;
	}
}

rule("[루시우] : 궁극기 - 진격의 거인 발동 by KISUM (특전관련 수정)")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Is Using Ultimate(Players On Hero(Hero(루시우), All Teams)) == True;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 루시우 : 무럭 무럭 자라라!", Hero Icon String(Hero(루시우))));
		Start Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 1.140,
			True);
		Play Effect(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)),
			Bad Pickup Effect, Color(Turquoise), Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우),
			All Teams)), 4);
		Play Effect(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), Ring Explosion,
			Color(Turquoise), Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 6);
		Wait(0.250, Ignore Condition);
		Start Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 1.280,
			True);
		Wait(0.250, Ignore Condition);
		Start Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 1.420,
			True);
		Wait(0.250, Ignore Condition);
		Start Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 1.560,
			True);
		Wait(0.250, Ignore Condition);
		Start Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 1.700,
			True);
		Wait(0.250, Ignore Condition);
		Start Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 1.840,
			True);
		Wait(0.250, Ignore Condition);
		Start Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 1.980,
			True);
		Wait(0.250, Ignore Condition);
		Start Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 2.120,
			True);
		Wait(0.250, Ignore Condition);
		Start Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 2.260,
			True);
		Wait(0.250, Ignore Condition);
		Start Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 2.400,
			True);
		Wait(2.250, Ignore Condition);
		Start Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 2.260,
			True);
		Wait(0.250, Ignore Condition);
		Start Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 2.120,
			True);
		Wait(0.250, Ignore Condition);
		Start Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 1.980,
			True);
		Wait(0.250, Ignore Condition);
		Start Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 1.840,
			True);
		Wait(0.250, Ignore Condition);
		Start Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 1.700,
			True);
		Wait(0.250, Ignore Condition);
		Start Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 1.560,
			True);
		Wait(0.250, Ignore Condition);
		Start Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 1.420,
			True);
		Wait(0.250, Ignore Condition);
		Start Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 1.280,
			True);
		Wait(0.250, Ignore Condition);
		Start Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)), 1.140,
			True);
		Wait(0.250, Ignore Condition);
		Stop Scaling Player(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(루시우), All Teams)));
		If(Players On Hero(Hero(자리야), All Teams).ttek_left_enable == True);
			Start Scaling Player(Players On Hero(Hero(자리야), All Teams), 0.334, True);
		Else If(Players On Hero(Hero(토르비욘), All Teams).ttek_right_enable == True);
			Start Scaling Player(Players On Hero(Hero(토르비욘), All Teams), 1.500, True);
		End;
	}
}

rule("[로드호그] : 능력 설명 + HOG1 + HOGBL by KISUM *")
{
	event
	{
		Ongoing - Each Player;
		All;
		로드호그;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 블라인드", Icon String(Poison), Event Player.HOGBL), Custom String(" 남은 쿨타임 {0}초",
			Event Player.HOGBL), Custom String(
			" F (상호작용키, 3R부터 활성화, 라운드 시간 내에만 사용 가능)\r\n 1. 사용 시 2초간 모든 적들의 시야를 차단함\r\n 2. 사용 시 로드호그의 수명 2R 단축", Event Player.HOGBL), Left,
			10, Color(Green), Color(Yellow), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 9, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}     돼재앙", Ability Icon String(Hero(로드호그), Button(Ultimate))), Null, Custom String(
			" Q\r\n 1. 전방의 적들을 밀쳐냄                     \r\n 2. 사용 시 로드호그의 수명 2R 단축                    "), Left, 6, Color(Green), Color(흰색),
			Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 5, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 돼지불족", Icon String(Fire)), Null, Custom String(
			" 패시브\n 로드호그의 공격을 받은 적에게 일정 시간 화상상태 부여                "), Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{1} 수명 {0}R", Event Player.HOG1, Icon String(Warning)), Null, Custom String(
			" 패시브\r\n 좌측에 표시된 라운드가 되면 로드호그 즉시 사망                          "), Left, 2, Color(Red), Color(흰색), Color(흰색), String,
			Visible Never);
		Event Player.HOG1 = 20;
		Event Player.HOGBL = 0;
	}
}

rule("[로드호그] : 블라인드 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		로드호그;
	}

	condition
	{
		Is Alive(Event Player) == True;
		Event Player.Z != 1;
		Is Button Held(Event Player, Button(Interact)) == True;
		Match Time <= 30;
		Global.RoundNumber >= 3;
		Global.RoundNumber != 420.690;
		Event Player.HOGBL == 0;
		Has Status(Event Player, Hacked) == False;
		Has Status(Event Player, Knocked Down) == False;
		Has Status(Event Player, Asleep) == False;
		Has Status(Event Player, Frozen) == False;
		Has Status(Event Player, Stunned) == False;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 로드호그 : 눈에 뵈는게 없지?", Hero Icon String(Hero(로드호그))));
		Event Player.HOG1 = Event Player.HOG1 + -2;
		Event Player.HOGBL = 3;
		Start Camera(Filtered Array(All Players(All Teams), Current Array Element != Event Player), Global.ArenaCentre + Vector(0, -200,
			0), Global.ArenaCentre + Vector(0, -500, 0), 0);
		Wait(1, Ignore Condition);
		Event Player.HOGBL = 2;
		Wait(1, Ignore Condition);
		Event Player.HOGBL = 1;
		Stop Camera(All Players(All Teams));
		Wait(1, Ignore Condition);
		Event Player.HOGBL = 0;
	}
}

rule("[로드호그] : 궁극기 - 생명 감소 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		로드호그;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Event Player.HOG1 = Event Player.HOG1 + -2;
	}
}

rule("[로드호그] : 블라인드 공간 생성 by KISUM")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Has Spawned(Players On Hero(Hero(로드호그), All Teams)) == True;
	}

	action
	{
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
		Create Effect(All Players(All Teams), Sphere, Color(Black), Global.ArenaCentre + Vector(0, -200, 0), 6,
			Visible To Position and Radius);
	}
}

rule("[로드호그] : Drug 사망 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		로드호그;
	}

	condition
	{
		Is Alive(Event Player) == True;
		Event Player.HOG1 <= Global.RoundNumber;
		Global.RoundNumber != 420.690;
	}

	action
	{
		Kill(Event Player, Null);
		Big Message(All Players(All Teams), Custom String("{0} 로드호그 : 내 수명이 다하다니... 분하다 분해!", Hero Icon String(Hero(로드호그))));
	}
}

rule("[로드호그] : 돼지불족 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		로드호그;
	}

	condition
	{
		Global.RoundNumber >= 0;
	}

	action
	{
		Set Status(Victim, Null, Burning, 1);
	}
}

rule("[애쉬] : 능력 설명 by KISUM *")
{
	event
	{
		Ongoing - Each Player;
		All;
		애쉬;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 저격", Ability Icon String(Hero(애쉬), Button(Primary Fire))), Null, Custom String(
			" 우클릭\r\n 적에게 0.7초간 스턴효과 부여 (적이 화상상태일 경우 0.15초)    "), Left, 6, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 5, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}  다이너마이트", Ability Icon String(Hero(애쉬), Button(Ability 2))), Null, Custom String(
			" E\r\n 다이너마이트에 맞아 화상상태인 적에게 간헐적 스턴상태 부여 "), Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
	}
}

rule("[애쉬] : 패시브 - 버닝 스턴 효과 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		애쉬;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Has Status(Victim, Burning) == True;
	}

	action
	{
		Set Status(Victim, Null, Stunned, 0.150);
	}
}

rule("[애쉬] : 패시브 - 일반 스턴 효과 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		애쉬;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Has Status(Victim, Burning) == False;
	}

	action
	{
		Set Status(Victim, Null, Stunned, 0.700);
	}
}

rule("[둠피스트] : 능력 설명 + D1 by KISUM *")
{
	event
	{
		Ongoing - Each Player;
		All;
		둠피스트;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create Progress Bar HUD Text(Players On Hero(Hero(둠피스트), All Teams), 11.111 * Global.DH, Custom String("{0}/9", Global.DH), Left,
			7, Color(Green), Color(흰색), Visible To Values and Color, Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 시간 연장", Icon String(Plus)), Null, Custom String(
			" R (재장전)\r\n 라운드시간 1초 연장 (기본 6번/특전 9번 사용 가능)     "), Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 자동 승리", Hero Icon String(Hero(둠피스트))), Null, Custom String(
			" 패시브\r\n 13라운드까지 생존시 자동 승리                                 "), Left, 2, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Global.DH = 6;
	}
}

rule("[둠피스트] : 패시브 - 승리 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		둠피스트;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Global.RoundNumber == 13;
		Global.RoundNumber != 420.690;
		Match Time <= 29;
	}

	action
	{
		Declare Player Victory(Event Player);
		Declare Team Victory(Team Of(Event Player));
		Big Message(All Players(All Teams), Custom String("둠피스트 : 너흰 날 이기지 못해!"));
	}
}

rule("[둠피스트] : 패시브 - 안내 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		둠피스트;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Global.RoundNumber == 1;
		Number Of Deaths(Event Player) < 1;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{1} {0} \"13라운드까지 나를 처치 못하면 게임은 나의 승리다!\"", Hero Icon String(Hero(둠피스트)),
			Icon String(Warning)));
	}
}

rule("[둠피스트] : 시간 연장 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		둠피스트;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Event Player.Z != 1;
		Match Time <= 29;
		Is Button Held(Event Player, Button(Reload)) == True;
		Global.DH >= 1;
		Has Status(Event Player, Hacked) == False;
		Has Status(Event Player, Knocked Down) == False;
		Has Status(Event Player, Asleep) == False;
		Has Status(Event Player, Frozen) == False;
		Has Status(Event Player, Stunned) == False;
	}

	action
	{
		Global.DH = Global.DH + -1;
		Set Match Time(Match Time + 1);
		Small Message(Filtered Array(All Players(All Teams), Current Array Element != Event Player), Custom String("{0} 둠피스트 : 1초 연장!",
			Hero Icon String(Hero(둠피스트))));
	}
}

rule("[둠피스트] : 연장 제한 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Custom String("{0}", Event Player) == Global.R;
	}

	action
	{
		Remove Player(Event Player);
	}
}

rule("[파라] : 능력 설명 by KISUM *")
{
	event
	{
		Ongoing - Each Player;
		All;
		파라;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 충격탄", Ability Icon String(Hero(파라), Button(Ability 2))), Null, Custom String(
			" E\n 충격탄에 맞은 적에게 1.2초간 스턴상태 부여                                   "), Left, 4, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 포화", Ability Icon String(Hero(파라), Button(Ultimate))), Null, Custom String(
			" Q\r\n 포화에 맞은 적에게 3초간 스턴상태 부여                                   "), Left, 2, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
	}
}

rule("[파라] : 포화 설명 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		파라;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 파라 : 놔 놔놔놔 놔놔 놔놔놔 놔 쏴", Hero Icon String(Hero(파라))));
	}
}

rule("[파라] : 스턴 (포화/충격탄) by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		파라;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		disabled Is Using Ultimate(Event Player) == True;
	}

	action
	{
		If(Is Using Ultimate(Event Player));
			Set Status(Victim, Null, Knocked Down, 3);
		Else;
			Set Status(Victim, Null, Knocked Down, 1.200);
		End;
	}
}

rule("[정크랫] : 능력 설명 by KISUM * (다수 수정, Dote6, 250511)")
{
	event
	{
		Ongoing - Each Player;
		All;
		정크랫;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 무적의 타이어", Ability Icon String(Hero(정크랫), Button(Ultimate))), Null, Custom String(
			" Q\n 1. 궁극기 사용 중 정크랫 무적 상태\n 2. 궁극기로 데미지를 준 플레이어에게 정크랫 순간이동"), Left, 10, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 9, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 등가 교환", Icon String(Skull)), Null, Custom String(
			" 패시브 (7라운드부터 발동, 궁극기 사용 중 미발동)\r\n 본인이 죽었는데 적에게 데미지를 주면, 적 처치 후 부활"), Left, 8, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 5, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 다잉 메시지", Ability Icon String(Hero(정크랫), Button(Ability 2))), Null, Custom String(
			" 패시브 (1회, 궁극기 사용 중 미발동)\n 죽은 장소 근처에 덫을 깔고 다시 죽음"), Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 피버 타임", Ability Icon String(Hero(정크랫), Button(Ability 1))), Null, Custom String(
			" 패시브\r\n 남은 시간이 3초 이하면, 충격 지뢰 무제한 사용 가능              "), Left, 2, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
	}
}

rule("[정크랫] : 다잉 메시지 (특전에서 기본으로 옮긴 뒤 수정, Dote6, 250506)")
{
	event
	{
		Player Died;
		All;
		정크랫;
	}

	condition
	{
		Event Player.junk_var[2] == 0;
		Is Using Ultimate(Event Player) == False;
	}

	action
	{
		Resurrect(Event Player);
		Teleport(Event Player, Vector(Random Real(-3, 3), Random Real(0, 1), Random Real(-3, 3)) + Event Player);
		Set Ability Cooldown(Event Player, Button(Ability 2), 0);
		Press Button(Event Player, Button(Ability 2));
		Wait(0.800, Ignore Condition);
		Event Player.junk_var[2] = 1;
		Clear Status(Event Player, Unkillable);
		Clear Status(Event Player, Phased Out);
		Kill(Event Player, Null);
	}
}

rule("[정크랫] : 궁극기 중 무적 (궁극기 중 만으로 수정, Dote6, 250511)")
{
	event
	{
		Ongoing - Each Player;
		All;
		정크랫;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Set Status(Event Player, Null, Phased Out, 9999);
		Create Effect(Filtered Array(All Players(All Teams), Current Array Element != Position Of(Event Player)), Good Aura, Color(Yellow),
			Event Player, 1, Visible To Position and Radius);
		Event Player.M2 = Last Created Entity;
		Wait Until(!Is Using Ultimate(Event Player), 99999);
		disabled Set Status(Event Player, Null, Unkillable, 3);
		disabled Create Progress Bar HUD Text(Event Player, 33.333 * (Evaluate Once(Total Time Elapsed + 3) - Total Time Elapsed), Custom String(
			"완전무적 종료까지 {0}초 남음!", Evaluate Once(Total Time Elapsed + 3) - Total Time Elapsed), Top, 9.100, Color(Yellow), Color(흰색),
			Visible To Values and Color, Default Visibility);
		disabled Event Player.junk_var[0] = Last Text ID;
		disabled Wait(3, Ignore Condition);
		Clear Status(Event Player, Phased Out);
		Destroy Effect(Event Player.M2);
		disabled Destroy Progress Bar HUD Text(Event Player.junk_var[0]);
	}
}

rule("[정크랫] : 궁극기 맞춘 적에게 이동")
{
	event
	{
		Player Dealt Damage;
		All;
		정크랫;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Teleport(Attacker, Position Of(Victim));
	}
}

rule("[정크랫] : 지뢰 개수 by KISUM (피버타임 및 특전으로 수정, Dote6, 250506)")
{
	event
	{
		Ongoing - Each Player;
		All;
		정크랫;
	}

	condition
	{
		Ability Charge(Event Player, Button(Ability 1)) < 2;
		(Match Time < 3 || Event Player.ttek_right_enable) == True;
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Set Ability Charge(Event Player, Button(Ability 1), 2);
	}
}

rule("[정크랫] : 피버 타임 개시 이펙트 (추가, Dote6, 250506)")
{
	event
	{
		Ongoing - Each Player;
		All;
		정크랫;
	}

	condition
	{
		Match Time < 3;
		Match Time > 0;
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Event Player.ttek_right_enable != True;
	}

	action
	{
		Create Progress Bar HUD Text(Event Player, 33.333 * Match Time, Custom String("피버타임 종료까지 {0}초 남음!", Match Time), Top, 9, Color(
			Orange), Color(흰색), Visible To Values and Color, Default Visibility);
		Event Player.junk_var[1] = Last Text ID;
		Wait Until(Match Time >= 3 || Match Time <= 0, 99999);
		Destroy Progress Bar HUD Text(Event Player.junk_var[1]);
	}
}

rule("[정크랫] : 패시브 - 죽으면 이펙트 삭제 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		정크랫;
	}

	condition
	{
		Is Dead(Event Player) == True;
	}

	action
	{
		Destroy Effect(Event Player.M2);
	}
}

rule("[정크랫] : 패시브 - 사망 이후 즉사 스킬 발동 by KISUM (궁으로는 발동 안되게 수정, Dote6, 250511)")
{
	event
	{
		Player Dealt Damage;
		All;
		정크랫;
	}

	condition
	{
		Event Player.Z != 1;
		Is Dead(Event Player) == True;
		Global.RoundNumber >= 7;
		Is Using Ultimate(Event Player) == False;
	}

	action
	{
		Damage(Victim, Attacker, 100000);
		Abort If(Is Alive(Victim));
		Small Message(Victim, Custom String("{0} 정크랫 : 고마워! 덕분에 부활할 수 있었어!", Hero Icon String(Hero(정크랫))));
		Resurrect(Event Player);
		Global.LivingPlayers = Append To Array(Global.LivingPlayers, Event Player);
		Set Player Score(Event Player, Global.RoundNumber);
		Set Status(Event Player, Null, Unkillable, 9999);
		Set Status(Event Player, Null, Phased Out, 9999);
		Create Effect(Filtered Array(All Players(All Teams), Current Array Element != Position Of(Event Player)), Good Aura, Color(Yellow),
			Event Player, 1, Visible To Position and Radius);
		Event Player.M2 = Last Created Entity;
		Create Progress Bar HUD Text(Event Player, 10 * Match Time, Custom String("완전무적 종료까지 {0}초 남음!", Match Time), Top, 9.100, Color(
			Yellow), Color(흰색), Visible To Values and Color, Default Visibility);
		Event Player.junk_var[0] = Last Text ID;
		Wait Until(Match Time > 60, 99999);
		Clear Status(Event Player, Unkillable);
		Clear Status(Event Player, Phased Out);
		Destroy Effect(Event Player.M2);
		Destroy Progress Bar HUD Text(Event Player.junk_var[0]);
	}
}

rule("[레킹볼] : 능력 설명 by KISUM *")
{
	event
	{
		Ongoing - Each Player;
		All;
		레킹볼;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 원기회복", Ability Icon String(Hero(레킹볼), Button(Ability 2))), Null, Custom String(
			" E\r\n 1. 레킹볼 속도 이상시 원래 이동속도로 즉시 회복                    \r\n 2. 주변의 적들에게 잠깐의 스턴상태 부여"), Left, 4, Color(Green), Color(흰색),
			Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}        넉다운", Hero Icon String(Hero(레킹볼))), Null, Custom String(
			" 패시브\r\n 레킹볼에 치이거나 궁극기에 맞은 적을 1.5초간 넉다운시킴         "), Left, 2, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create Effect(Event Player, Ring, Color(Blue), Event Player, 7.500, Visible To Position and Radius);
		Event Player.SA = Last Created Entity;
	}
}

rule("[레킹볼] : 속도이상 무효화 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		레킹볼;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Is Using Ability 2(Event Player) == True;
	}

	action
	{
		Set Move Speed(Event Player, 120);
		Small Message(Event Player, Custom String("{0} 레킹볼 : 변속 무효화 발동!", Hero Icon String(Hero(레킹볼))));
		Event Player.M = Players Within Radius(Event Player, 7.500, Opposite Team Of(Team Of(Event Player)), Surfaces);
		Event Player.M = Filtered Array(Event Player.M, Current Array Element != Event Player);
		Set Status(Event Player.M, Event Player, Stunned, 0.500);
		Small Message(Event Player.M, Custom String("{0} 레킹볼 : sorry", Hero Icon String(Hero(레킹볼))));
	}
}

rule("[레킹볼] : 넉다운 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		레킹볼;
	}

	condition
	{
		Global.RoundNumber >= 0;
	}

	action
	{
		Set Status(Victim, Null, Knocked Down, 1.500);
		Small Message(Victim, Custom String("{0} 레킹볼 : 빡쳐?", Hero Icon String(Hero(레킹볼))));
	}
}

rule("[윈스턴] : 능력 설명 by KISUM *")
{
	event
	{
		Ongoing - Each Player;
		All;
		윈스턴;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 방향키 전환", Icon String(Question Mark)), Null, Custom String(
			" Q (라운드시간 내에서만 사용 가능, 승자결정전에서 사용시 효과 없음)\r\n 1. 라운드시간을 7.5초로 조정\r\n 2. 모든 적들의 방향키를 2.5초 간격으로 반전→정상화→반전시킴"), Left, 6, Color(
			Green), Color(흰색), Color(흰색), None, Visible Never);
	}
}

rule("[윈스턴] : 궁극기 사용 불가 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		윈스턴;
	}

	condition
	{
		Match Time > 30;
	}

	action
	{
		Disallow Button(Event Player, Button(Ultimate));
	}
}

rule("[윈스턴] : 궁극기 사용 가능 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		윈스턴;
	}

	condition
	{
		Match Time <= 30;
	}

	action
	{
		Allow Button(Event Player, Button(Ultimate));
	}
}

rule("[윈스턴] : 방향키 전환 Big Message by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		윈스턴;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
		Global.RoundNumber != 420.690;
		Match Time <= 30;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 윈스턴 : 화가난다!!!!!!", Hero Icon String(Hero(윈스턴))));
		Set Match Time(7.500);
	}
}

rule("[윈스턴] : 방향키 전환 발동 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Is Using Ultimate(Players On Hero(Hero(윈스턴), All Teams)) == True;
		Event Player != Players On Hero(Hero(윈스턴), All Teams);
		Global.RoundNumber != 420.690;
		Match Time <= 30;
	}

	action
	{
		Start Transforming Throttle(Event Player, 0, 0, Direction From Angles(Horizontal Facing Angle Of(Event Player) + 180, 0));
		Small Message(Event Player, Custom String("{0} 윈스턴 : 방향키가 반전되니 어때?", Hero Icon String(Hero(윈스턴))));
		Wait(2.500, Ignore Condition);
		Stop Transforming Throttle(Event Player);
		Wait(2.500, Ignore Condition);
		Start Transforming Throttle(Event Player, 0, 0, Direction From Angles(Horizontal Facing Angle Of(Event Player) + 180, 0));
		Wait(2.500, Ignore Condition);
		Stop Transforming Throttle(Event Player);
	}
}

rule("[윈스턴] : 사망시 방향키 전환 해제 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		윈스턴;
	}

	condition
	{
		Is Dead(Event Player) == True;
	}

	action
	{
		Stop Transforming Throttle(Filtered Array(All Players(All Teams), Current Array Element != Event Player));
	}
}

rule("[윈스턴] : 나가면 방향키 전환 해제 by KISUM")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Entity Exists(Players On Hero(Hero(윈스턴), All Teams)) == False;
	}

	action
	{
		Stop Transforming Throttle(Filtered Array(All Players(All Teams), Current Array Element != Players On Hero(Hero(윈스턴), All Teams)));
	}
}

rule("[에코] : 능력 설명 + ECHO1 by KISUM *")
{
	event
	{
		Ongoing - Each Player;
		All;
		에코;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 점착 폭탄", Ability Icon String(Hero(에코), Button(Secondary Fire))), Null,
			Custom String(" 우클릭 (3라운드부터 사용 가능)\r\n 1. 일정량 이상 공격에 맞은 적이 즉시 사망 (본인 포함)\r\n 2. 킬 성공 여부에 따라 쿨타임 상이 (성공시 75초, 실패시 20초)"), Left,
			8, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 광선 집중", Ability Icon String(Hero(에코), Button(Ability 2))), Null, Custom String(
			" E (3라운드부터 사용 가능)\r\n 1. 공격에 맞은 적이 즉시 사망 (사망자 발생 즉시 공격 중단)\r\n 2. 킬 성공 여부에 따라 쿨타임 상이 (성공시 50초, 실패시 20초)"), Left, 4, Color(
			Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}  양자택일", Hero Icon String(Hero(에코))), Null, Custom String(
			" 패시브\r\n 광선 집중 또는 점착 폭탄 중 단 1개의 스킬만 사용 가능"), Left, 2, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Event Player.ECHO1 = 0;
	}
}

rule("[에코] : 스킬 - 즉시 사망 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		에코;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Kill(Victim, Attacker);
		Small Message(Victim, Custom String("{0} 에코 : 나를 만만하게 본 죄값이야!", Hero Icon String(Hero(에코))));
		Cancel Primary Action(Event Player);
		Wait(0.500, Ignore Condition);
		Set Ability Cooldown(Event Player, Button(Ability 2), 50);
		Set Ability Cooldown(Event Player, Button(Secondary Fire), 75);
	}
}

rule("[에코] : 스킬 생성 3라운드 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		에코;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Global.RoundNumber == 3;
		Event Player.ECHO1 == 0;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 에코 : 스킬 획득! 제게 공격받으면 즉시 사망하실거에요!", Hero Icon String(Hero(에코))));
		Create Effect(Filtered Array(All Players(All Teams), Current Array Element != Position Of(Event Player)), Bad Aura, Color(Aqua),
			Event Player, 1, Visible To Position and Radius);
		Event Player.M = Last Created Entity;
		Play Effect(All Players(All Teams), Bad Pickup Effect, Color(Sky Blue), Event Player, 2);
		Play Effect(All Players(All Teams), Ring Explosion, Color(흰색), Event Player, 3);
		Event Player.ECHO1 = 1;
		Set Ability 2 Enabled(Event Player, True);
		Set Secondary Fire Enabled(Event Player, True);
	}
}

rule("[에코] : 광선 집중 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		에코;
	}

	condition
	{
		Is Using Ability 2(Event Player) == True;
		Event Player.ECHO1 == 1;
	}

	action
	{
		Set Secondary Fire Enabled(Event Player, False);
	}
}

rule("[에코] : 점착 폭탄 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		에코;
	}

	condition
	{
		Is Firing Secondary(Event Player) == True;
		Event Player.ECHO1 == 1;
	}

	action
	{
		Set Ability 2 Enabled(Event Player, False);
	}
}

rule("[에코] : 죽으면 이펙트 삭제 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		에코;
	}

	condition
	{
		Is Dead(Event Player) == True;
	}

	action
	{
		Destroy Effect(Event Player.M);
	}
}

rule("[키리코] : 능력 설명 by KISUM *")
{
	event
	{
		Ongoing - Each Player;
		All;
		키리코;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Global.K_ALREADYUSED = 3;
		Create Progress Bar HUD Text(Players On Hero(Hero(키리코), All Teams), 33.340 * Global.K_ALREADYUSED, Custom String("{0}/3",
			Global.K_ALREADYUSED), Left, 13, Color(Green), Color(흰색), Values, Visible Never);
		Create HUD Text(Event Player, Custom String("{0}  체인지셀", Icon String(Recycle)), Null, Custom String(
			" R (재장전 / 라운드별 1회 · 총 3회 사용 가능, 승자결정전 사용 불가)\r\n 키리코가 위치한 셀을 제시된 색으로 변경하여 생존이 가능한 셀로 바꿈"), Left, 12, Color(Green), Color(흰색),
			Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 11, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}  페이크셀", Icon String(Spiral)), Null, Custom String(
			" F (상호작용 / 각 라운드 시간 내 1회 사용 가능)\r\n 키리코가 위치한 자리에 제시된 색과 같은 색의 페이크셀을 생성함       "), Left, 10, Color(Green), Color(흰색), Color(
			흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 9, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}  순간이동", Icon String(Flag)), Null, Custom String(
			" SHIFT (여우길이 활성화된 동안 사용 가능, 에임필요)\r\n 1. 살아있는 적들 중 조준선에서 가장 가까운 적에게 이동\r\n 2. 죽은 적에게 사용하거나 에임이 안맞으면 장외 및 낙사 판정될 수 있음"), Left,
			8, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 여우길", Ability Icon String(Hero(키리코), Button(Ultimate))), Null, Custom String(
			" Q\r\n 설치된 동안 순간이동 사용 가능                                                            "), Left, 2, Color(Green), Color(흰색),
			Color(흰색), None, Visible Never);
	}
}

rule("[키리코] : 여우길 - 안내 메세지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		키리코;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 키리코 : 여우 신이시여 제게 능력을!", Hero Icon String(Hero(키리코))));
	}
}

rule("[키리코] : 여우길 - 발동 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		키리코;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
		Is Button Held(Event Player, Button(Ability 1)) == True;
		Has Status(Event Player, Hacked) == False;
		Has Status(Event Player, Knocked Down) == False;
		Has Status(Event Player, Asleep) == False;
		Has Status(Event Player, Frozen) == False;
		Has Status(Event Player, Rooted) == False;
		Has Status(Event Player, Stunned) == False;
		Is In View Angle(Event Player, Player Closest To Reticle(Event Player, All Teams), 90) == True;
	}

	action
	{
		Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams) != Is Dead(
			Player Closest To Reticle(Event Player, All Teams))).Kiriko_Tele = 1;
	}
}

rule("[키리코] : 순간이동 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Event Player.Kiriko_Tele == 1;
	}

	action
	{
		Teleport(Players On Hero(Hero(키리코), All Teams), Vector(0, 0.500, 0) + Event Player);
		Small Message(Event Player, Custom String("{0} 키리코 : 덕분에 순간이동 할 수 있었어", Hero Icon String(Hero(키리코))));
		Event Player.Kiriko_Tele = 0;
	}
}

rule("[키리코] : 페이크셀 생성 White by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		키리코;
	}

	condition
	{
		Is Button Held(Event Player, Button(Interact)) == True;
		Match Time <= 30;
		Event Player.KRK_C1 == 0;
		Is Alive(Event Player) == True;
	}

	action
	{
		Event Player.KRK_C1 = Event Player.KRK_C1 + 1;
		Play Effect(All Players(All Teams), Good Pickup Effect, Color(흰색), Event Player, 3);
		If(Global.CorrectColour == 1);
			Create Effect(All Players(All Teams), Sphere, Color(흰색), Position Of(Event Player), 3, None);
		Else If(Global.CorrectColour == 2);
			Create Effect(All Players(All Teams), Sphere, Color(Yellow), Position Of(Event Player), 3, None);
		Else If(Global.CorrectColour == 3);
			Create Effect(All Players(All Teams), Sphere, Color(Green), Position Of(Event Player), 3, None);
		Else If(Global.CorrectColour == 4);
			Create Effect(All Players(All Teams), Sphere, Color(Purple), Position Of(Event Player), 3, None);
		Else If(Global.CorrectColour == 5);
			Create Effect(All Players(All Teams), Sphere, Color(Red), Position Of(Event Player), 3, None);
		Else If(Global.CorrectColour == 6);
			Create Effect(All Players(All Teams), Sphere, Color(Blue), Position Of(Event Player), 3, None);
		Else If(Global.CorrectColour == 7);
			Create Effect(All Players(All Teams), Sphere, Color(Orange), Position Of(Event Player), 3, None);
		Else If(Global.CorrectColour == 8);
			Create Effect(All Players(All Teams), Sphere, Color(Aqua), Position Of(Event Player), 3, None);
		End;
		Event Player.KRK_CELL1 = Last Created Entity;
	}
}

rule("[키리코] : 페이크셀 제거 by KISUM (특전관련 수정)")
{
	event
	{
		Ongoing - Each Player;
		All;
		키리코;
	}

	condition
	{
		Match Time > 30;
	}

	action
	{
		Destroy Effect(Event Player.KRK_CELL1);
		Event Player.KRK_C1 = 0;
		Destroy Effect(Event Player.KRK_CELL2);
		Event Player.KRK_CELL2 = 0;
	}
}

rule("[키리코] : 체인지셀 with Dote6, YaksuStn")
{
	event
	{
		Ongoing - Each Player;
		All;
		키리코;
	}

	condition
	{
		Is Button Held(Event Player, Button(Reload)) == True;
		Match Round <= 20;
		Match Time <= 30;
		Is Alive(Event Player) == True;
		Global.K_ALREADYUSED > 0;
		Global.K_ALREADYUSED_R == 0;
		Has Status(Event Player, Hacked) == False;
		Has Status(Event Player, Knocked Down) == False;
		Has Status(Event Player, Asleep) == False;
		Has Status(Event Player, Frozen) == False;
		Has Status(Event Player, Stunned) == False;
	}

	action
	{
		For Global Variable(INDEX, 0, Count Of(Global.SphereLocations) + 0, 1);
			If(Distance Between(Global.SphereLocations[Global.INDEX], Position Of(Event Player)) <= 3.200);
				If(Global.Colours[Global.INDEX] == Global.CorrectColour);
					Big Message(Event Player, Custom String("{0} 바꿀 수 없는 셀입니다!", Icon String(Warning)));
					Break;
				End;
				Global.K_ALREADYUSED = Global.K_ALREADYUSED + -1;
				Big Message(All Players(All Teams), Custom String("{0} 키리코 : 뭔가 달라지지 않았나요? (데헷)", Hero Icon String(Hero(키리코))));
				Destroy Effect(Global.SphereID[Global.INDEX]);
				Wait(0.016, Ignore Condition);
				Play Effect(All Players(All Teams), Buff Explosion Sound, Color(흰색), Global.SphereLocations[Global.INDEX], 200);
				Wait(0.016, Ignore Condition);
				Play Effect(All Players(All Teams), Bad Explosion, Color(흰색), Global.SphereLocations[Global.INDEX], 200);
				Wait(0.016, Ignore Condition);
				If(Global.CorrectColour == 1);
					Create Effect(All Players(All Teams), Sphere, Color(흰색), Global.SphereLocations[Global.INDEX], 3, Position and Radius);
				Else If(Global.CorrectColour == 2);
					Create Effect(All Players(All Teams), Sphere, Color(Yellow), Global.SphereLocations[Global.INDEX], 3, Position and Radius);
				Else If(Global.CorrectColour == 3);
					Create Effect(All Players(All Teams), Sphere, Color(Green), Global.SphereLocations[Global.INDEX], 3, Position and Radius);
				Else If(Global.CorrectColour == 4);
					Create Effect(All Players(All Teams), Sphere, Color(Purple), Global.SphereLocations[Global.INDEX], 3, Position and Radius);
				Else If(Global.CorrectColour == 5);
					Create Effect(All Players(All Teams), Sphere, Color(Red), Global.SphereLocations[Global.INDEX], 3, Position and Radius);
				Else If(Global.CorrectColour == 6);
					Create Effect(All Players(All Teams), Sphere, Color(Blue), Global.SphereLocations[Global.INDEX], 3, Position and Radius);
				Else If(Global.CorrectColour == 7);
					Create Effect(All Players(All Teams), Sphere, Color(Orange), Global.SphereLocations[Global.INDEX], 3, Position and Radius);
				Else If(Global.CorrectColour == 8);
					Create Effect(All Players(All Teams), Sphere, Color(Aqua), Global.SphereLocations[Global.INDEX], 3, Position and Radius);
				End;
				Wait(0.050, Ignore Condition);
				Global.SphereID[Global.INDEX] = Last Created Entity;
				Global.TRUE_VECTOR = Global.SphereLocations[Global.INDEX];
				Global.rightindex = Global.INDEX;
				Wait Until(Match Time <= 0.070, 9999);
				Global.TRUE_VECTOR = Global.SphereLocations[Global.rightindex];
			End;
			Wait(0.016, Ignore Condition);
		End;
	}
}

rule("[키리코] : 체인지셀 생존 with Dote6, YaksuStn")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Players Within Radius(Global.TRUE_VECTOR, 3.100, All Teams, Off) == True;
		Match Time < 0.050;
	}

	action
	{
		Players Within Radius(Global.TRUE_VECTOR, 3.100, All Teams, Off).p_ModeIdeaOwner = 2;
	}
}

rule("[라이프위버] : 능력 설명 by KISUM *")
{
	event
	{
		Ongoing - Each Player;
		All;
		라이프위버;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 크고 아름다워", Ability Icon String(Hero(라이프위버), Button(Ultimate))), Null,
			Custom String(
			" Q\r\n 1. 15초간 크고 아름다운 무언가가 길을 가로막음\r\n 2. 모든 적들의 스킬을 끊고 15초간 점프를 제한함\r\n 3. 모든 적들의 궁극기 게이지 일정량을 주기적으로 감소시킴     "), Left, 4,
			Color(Green), Color(흰색), Color(흰색), None, Visible Never);
	}
}

rule("[라이프위버] : 궁극기 - 안내 메세지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		라이프위버;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 라이프위버 : 치유와 함께 무릎 관절을 제어해드릴게요.", Hero Icon String(Hero(라이프위버))));
	}
}

rule("[라이프위버] : 궁극기 - 점프 제한 + 궁게이지 감소 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Is Using Ultimate(Players On Hero(Hero(라이프위버), All Teams)) == True;
	}

	action
	{
		Set Status(Filtered Array(Event Player, Current Array Element != Players On Hero(Hero(라이프위버), All Teams)), Null, Hacked, 0.100);
		Set Jump Enabled(Filtered Array(Event Player, Current Array Element != Players On Hero(Hero(라이프위버), All Teams)), False);
		Wait(1.750, Ignore Condition);
		Set Ultimate Charge(Filtered Array(Event Player, Current Array Element != Players On Hero(Hero(라이프위버), All Teams)),
			Ultimate Charge Percent(Event Player) + -6);
		Wait(1.750, Ignore Condition);
		Set Ultimate Charge(Filtered Array(Event Player, Current Array Element != Players On Hero(Hero(라이프위버), All Teams)),
			Ultimate Charge Percent(Event Player) + -6);
		Wait(1.750, Ignore Condition);
		Set Ultimate Charge(Filtered Array(Event Player, Current Array Element != Players On Hero(Hero(라이프위버), All Teams)),
			Ultimate Charge Percent(Event Player) + -6);
		Wait(1.750, Ignore Condition);
		Set Ultimate Charge(Filtered Array(Event Player, Current Array Element != Players On Hero(Hero(라이프위버), All Teams)),
			Ultimate Charge Percent(Event Player) + -6);
		Wait(1.750, Ignore Condition);
		Set Ultimate Charge(Filtered Array(Event Player, Current Array Element != Players On Hero(Hero(라이프위버), All Teams)),
			Ultimate Charge Percent(Event Player) + -6);
		Wait(1.750, Ignore Condition);
		Set Ultimate Charge(Filtered Array(Event Player, Current Array Element != Players On Hero(Hero(라이프위버), All Teams)),
			Ultimate Charge Percent(Event Player) + -6);
		Wait(1.750, Ignore Condition);
		Set Ultimate Charge(Filtered Array(Event Player, Current Array Element != Players On Hero(Hero(라이프위버), All Teams)),
			Ultimate Charge Percent(Event Player) + -6);
		Wait(1.750, Ignore Condition);
		Set Ultimate Charge(Filtered Array(Event Player, Current Array Element != Players On Hero(Hero(라이프위버), All Teams)),
			Ultimate Charge Percent(Event Player) + -6);
		Wait(1.750, Ignore Condition);
		Set Ultimate Charge(Filtered Array(Event Player, Current Array Element != Players On Hero(Hero(라이프위버), All Teams)),
			Ultimate Charge Percent(Event Player) + -6);
		Set Jump Enabled(Filtered Array(Event Player, Current Array Element != Players On Hero(Hero(라이프위버), All Teams)), True);
	}
}

rule("[정커퀸] : 능력 설명 by KISUM * (정커퀸 특전으로 인한 수정 by Dote6)")
{
	event
	{
		Ongoing - Each Player;
		All;
		정커퀸;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 입체기동 톱니칼", Ability Icon String(Hero(정커퀸), Button(Secondary Fire))), Null,
			Custom String(" 우클릭→(0.5초 이내) 우클릭\n 바라보는 방향으로 짧게 이동함"), Left, 8, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Event Player.queen_var[8] = Last Text ID;
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}     지휘의 외침", Ability Icon String(Hero(정커퀸), Button(Ability 1))), Null,
			Custom String(" E\n 지휘의 외침 사용 동안 흡혈 7배 적용"), Left, 6, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 5, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}             흡혈", Hero Icon String(Hero(정커퀸))), Null, Custom String(
			" 패시브\n 흡혈 1,111회 성공 시 정커퀸 게임 승리"), Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
	}
}

rule("[정커퀸] : 패시브 - 승리 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		정커퀸;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Global.JQC >= 1111;
	}

	action
	{
		Declare Player Victory(Event Player);
		Declare Team Victory(Team Of(Event Player));
		Big Message(All Players(All Teams), Custom String("{0} 정커퀸 : 피 맛 좋네!", Hero Icon String(Hero(정커퀸))));
	}
}

rule("[정커퀸] : 패시브 - 안내 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		정커퀸;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Global.RoundNumber == 1;
		Number Of Deaths(Event Player) < 1;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{1} {0} \"내가 1,111번 흡혈하면 게임은 나의 승리다!\"", Hero Icon String(Hero(정커퀸)),
			Icon String(Warning)));
	}
}

rule("[정커퀸] : 흡혈 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		정커퀸;
	}

	condition
	{
		Is Alive(Event Player) == True;
	}

	action
	{
		Abort If Condition Is False;
		Global.JQC = Global.JQC + 1;
		Wait(0.016, Ignore Condition);
		If(Is Using Ability 1(Event Player) == True);
			Global.JQC = Global.JQC + 6;
		End;
	}
}

rule("[정커퀸] : 흡혈 - 게이지 표시 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Has Spawned(Players On Hero(Hero(정커퀸), All Teams)) == True;
	}

	action
	{
		Create Progress Bar HUD Text(Event Player, 0.090 * Global.JQC, Custom String("{1} 정커퀸 흡혈 1,111회 성공 시 정커퀸 승리! 현재 {0}회 성공!",
			Global.JQC, Hero Icon String(Hero(정커퀸))), Top, 6, Color(Blue), Color(흰색), Visible To and Values, Default Visibility);
		Event Player.JQC_GAGE = Last Text ID;
	}
}

rule("[정커퀸] : 흡혈 - 사망시 게이지 삭제 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Is Dead(Players On Hero(Hero(정커퀸), All Teams)) == True;
	}

	action
	{
		Destroy Progress Bar HUD Text(Event Player.JQC_GAGE);
	}
}

rule("[정커퀸] : 흡혈 - 퇴장시 게이지 삭제 by KISUM")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Entity Exists(Players On Hero(Hero(정커퀸), All Teams)) == False;
	}

	action
	{
		Destroy Progress Bar HUD Text(All Players(All Teams).JQC_GAGE);
	}
}

rule("[정커퀸] : 흡혈 - 부활시 게이지 표시 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Players On Hero(Hero(정커퀸), All Teams).RV_GAGE == 1;
	}

	action
	{
		Create Progress Bar HUD Text(Event Player, 0.090 * Global.JQC, Custom String("{1} 정커퀸 흡혈 1,111회 성공 시 정커퀸 승리! 현재 {0}회 성공!",
			Global.JQC, Hero Icon String(Hero(정커퀸))), Top, 6, Color(Blue), Color(흰색), Visible To Values and Color, Default Visibility);
		Event Player.JQC_GAGE = Last Text ID;
	}
}

rule("[정커퀸] : 입체기동 톱니칼: 활성화 (II 특전 선택시 비활성화 by Dote6)")
{
	event
	{
		Ongoing - Each Player;
		All;
		정커퀸;
	}

	condition
	{
		Is Firing Secondary(Event Player) == True;
		Event Player.ttek_right_enable != True;
	}

	action
	{
		Event Player.can_knife = True;
		Wait(0.500, Ignore Condition);
		Event Player.can_knife = False;
	}
}

rule("[정커퀸] : 입체기동 톱니칼: 이동 (II 특전 선택시 비활성화 by Dote6)")
{
	event
	{
		Ongoing - Each Player;
		All;
		정커퀸;
	}

	condition
	{
		Is Firing Secondary(Event Player) == True;
		Event Player.ttek_right_enable != True;
	}

	action
	{
		Wait Until(!Is Button Held(Event Player, Button(Secondary Fire)), 99999);
		Wait Until(Is Button Held(Event Player, Button(Secondary Fire)), 0.500);
		Abort If(Event Player.can_knife == False);
		Apply Impulse(Event Player, Facing Direction Of(Event Player) + Vector(0, 0.100, 0), 30, To World, Cancel Contrary Motion);
	}
}

rule("[일리아리] : 능력 설명 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		일리아리;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0}    스턴건", Ability Icon String(Hero(일리아리), Button(Primary Fire))), Null,
			Custom String(" 좌클릭\n 적중한 적에게 0.5초간 스턴상태 부여                    "), Left, 8, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0}      분출", Ability Icon String(Hero(일리아리), Button(Ability 1))), Null,
			Custom String(" SHIFT\r\n 1. 주위의 적을 넉백\r\n 2. 넉백당한 적에게 0.5초간 스턴상태 부여                     "), Left, 4, Color(Green), Color(흰색),
			Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3.500, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 태양 작렬", Ability Icon String(Hero(일리아리), Button(Ultimate))), Null, Custom String(
			" Q\r\n 궁극기 사용 중 피해를 받은 모든 적들에게 2.5초간 스턴상태 부여"), Left, 3, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 2.500, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 태양 구슬", Hero Icon String(Hero(일리아리))), Null, Custom String(
			" 패시브\r\n 공격에 맞은 적에게 태양 구슬을 씌워 시야를 방해함"), Left, 2, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
	}
}

rule("[일리아리] : 궁극기 - 스턴 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		일리아리;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Set Status(Victim, Null, Stunned, 2.500);
		Small Message(Victim, Custom String("{0} 일리아리 : 이걸 못피해?", Hero Icon String(Hero(일리아리))));
	}
}

rule("[일리아리] : 기본공격 - 스턴 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		일리아리;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Is Using Ultimate(Event Player) == False;
	}

	action
	{
		Set Status(Victim, Null, Stunned, 0.500);
		Small Message(Victim, Custom String("{0} 일리아리 : 불만있어?", Hero Icon String(Hero(일리아리))));
	}
}

rule("[일리아리] : 탄창 by KISUM (버그수정)")
{
	event
	{
		Ongoing - Each Player;
		All;
		일리아리;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Is Firing Primary(Event Player) == True;
	}

	action
	{
		Set Ammo(Event Player, 0, 0);
	}
}

rule("[일리아리] : 공격 - 색 구슬 by KISUM")
{
	event
	{
		Player Took Damage;
		All;
		All;
	}

	condition
	{
		Attacker == Players On Hero(Hero(일리아리), All Teams);
		Is Meleeing(Attacker) == False;
	}

	action
	{
		Set Status(Filtered Array(Event Player, Event Player == Players On Hero(Hero(라인하르트), All Teams)), Null, Hacked, 0.100);
		Disallow Button(Filtered Array(Event Player, Event Player == Players On Hero(Hero(라인하르트), All Teams)), Button(Secondary Fire));
		Set Status(Filtered Array(Event Player, Event Player == Players On Hero(Hero(레킹볼), All Teams)), Null, Hacked, 0.100);
		Disallow Button(Filtered Array(Event Player, Event Player == Players On Hero(Hero(레킹볼), All Teams)), Button(Ability 1));
		Set Status(Filtered Array(Event Player, Event Player == Players On Hero(Hero(브리기테), All Teams)), Null, Hacked, 0.100);
		Disallow Button(Filtered Array(Event Player, Event Player == Players On Hero(Hero(브리기테), All Teams)), Button(Secondary Fire));
		Create Effect(All Players(All Teams), Sphere, Color(Orange), Event Player, 1.800, Visible To Position and Radius);
		Event Player.ILL1 = Last Created Entity;
		Create Effect(All Players(All Teams), Sphere, Color(Red), Event Player, 1.800, Visible To Position and Radius);
		Event Player.ILL2 = Last Created Entity;
		Create Effect(All Players(All Teams), Sphere, Color(Orange), Event Player, 1.800, Visible To Position and Radius);
		Event Player.ILL3 = Last Created Entity;
		Create Effect(All Players(All Teams), Sphere, Color(Red), Event Player, 1.800, Visible To Position and Radius);
		Event Player.ILL4 = Last Created Entity;
		Create Effect(All Players(All Teams), Sphere, Color(Orange), Event Player, 1.800, Visible To Position and Radius);
		Event Player.ILL5 = Last Created Entity;
		Wait(2, Ignore Condition);
		Allow Button(Filtered Array(Event Player, Event Player == Players On Hero(Hero(라인하르트), All Teams)), Button(Secondary Fire));
		Allow Button(Filtered Array(Event Player, Event Player == Players On Hero(Hero(레킹볼), All Teams)), Button(Ability 1));
		Allow Button(Filtered Array(Event Player, Event Player == Players On Hero(Hero(브리기테), All Teams)), Button(Secondary Fire));
		Destroy Effect(Event Player.ILL1);
		Destroy Effect(Event Player.ILL2);
		Destroy Effect(Event Player.ILL3);
		Destroy Effect(Event Player.ILL4);
		Destroy Effect(Event Player.ILL5);
	}
}

rule("[라마트라] : 능력 설명 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		라마트라;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 응징", Ability Icon String(Hero(라마트라), Button(Ability 1))), Null, Custom String(
			" 좌클릭 (네메시스 폼에서만 사용 가능)\r\n 피해를 준 적에게 0.75초간 스턴상태 부여          "), Left, 6, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 5, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 절멸", Ability Icon String(Hero(라마트라), Button(Ultimate))), Null, Custom String(
			" Q\n 범위의 주변 적들에게 해킹상태 부여                "), Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
	}
}

rule("[라마트라] : 궁극기 - 해킹 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		라마트라;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Set Status(Victim, Null, Hacked, 0.250);
	}
}

rule("[라마트라] : 네메시스 - 좌클릭 허용 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		라마트라;
	}

	condition
	{
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Set Primary Fire Enabled(Event Player, True);
	}
}

rule("[라마트라] : 응징 - 스턴 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		라마트라;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Set Status(Victim, Null, Stunned, 0.750);
	}
}

rule("[라마트라] : 좌클릭 비허용 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		라마트라;
	}

	condition
	{
		Is Using Ability 1(Event Player) == False;
	}

	action
	{
		Set Primary Fire Enabled(Event Player, False);
	}
}

rule("[소전] : 능력 설명 by KISUM *")
{
	event
	{
		Ongoing - Each Player;
		All;
		소전;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 분열 사격", Ability Icon String(Hero(소전), Button(Ability 2))), Null, Custom String(
			" E\r\n 분열 사격 내부 적에게 일정 시간 화상상태 부여                    "), Left, 6, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 5, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 파워 슬라이드", Ability Icon String(Hero(소전), Button(Ability 1))), Null, Custom String(
			" SHIFT\r\n 슬라이드 동선에 있는 적들을 2.5초간 넉다운시킴               "), Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 궁극의 레일건", Ability Icon String(Hero(소전), Button(Ultimate))), Null, Custom String(
			" 우클릭 (궁극기 활성화 중에만 사용 가능)\n 공격을 받은 적에게 2.5초간 스턴상태 부여                    "), Left, 2, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
	}
}

rule("[소전] : 궁극기 - 스턴 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		소전;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Is Using Ultimate(Event Player) == True;
		Is Button Held(Event Player, Button(Secondary Fire)) == True;
	}

	action
	{
		Set Status(Victim, Null, Stunned, 2.500);
	}
}

rule("[소전] : 파워 슬라이드 - 넉다운 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		소전;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Event Player.SJ_SL = Players Within Radius(Event Player, 2, Opposite Team Of(Team Of(Event Player)), Surfaces);
		Event Player.SJ_SL = Filtered Array(Event Player.SJ_SL, Current Array Element != Event Player);
		Play Effect(All Players(All Teams), Bad Explosion, Color(Red), Event Player, 0.500);
		Play Effect(All Players(All Teams), Ring Explosion, Color(흰색), Event Player, 3);
		Set Status(Event Player.SJ_SL, Event Player, Knocked Down, 2.500);
		Small Message(Event Player.SJ_SL, Custom String("{0} 소전 : 잠시 지나가실게요!", Hero Icon String(Hero(소전))));
		Wait(0.050, Ignore Condition);
		Event Player.SJ_SL = Players Within Radius(Event Player, 2, Opposite Team Of(Team Of(Event Player)), Surfaces);
		Event Player.SJ_SL = Filtered Array(Event Player.SJ_SL, Current Array Element != Event Player);
		Set Status(Event Player.SJ_SL, Event Player, Knocked Down, 2.500);
		Small Message(Event Player.SJ_SL, Custom String("{0} 소전 : 잠시 지나가실게요!", Hero Icon String(Hero(소전))));
		Wait(0.050, Ignore Condition);
		Loop If Condition Is True;
	}
}

rule("[소전] : 분열 사격 - 화상 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		소전;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Set Status(Victim, Null, Burning, 1);
	}
}

rule("[소전] : 주무기 사용불가 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		소전;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Set Primary Fire Enabled(Event Player, False);
	}
}

rule("[소전] : 우클릭 허용 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		소전;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Set Secondary Fire Enabled(Event Player, True);
	}
}

rule("[소전] : 우클릭 비허용 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		소전;
	}

	condition
	{
		Is Using Ultimate(Event Player) == False;
	}

	action
	{
		Set Secondary Fire Enabled(Event Player, False);
	}
}

rule("[마우가] : 능력 설명 by KISUM *")
{
	event
	{
		Ongoing - Each Player;
		All;
		마우가;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 화염 넉백", Ability Icon String(Hero(마우가), Button(Primary Fire))), Null,
			Custom String(" 좌클릭\r\n 1. 연속으로 공격에 맞은 적에게 일정 시간 화상상태 부여               \r\n 2. 화상상태의 적에게 약간의 넉백효과 부여     "), Left, 2.400,
			Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 2.200, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 무릉도원", Ability Icon String(Hero(마우가), Button(Ultimate))), Null, Custom String(
			" Q (라운드시간 내에서만 사용 가능, 승자결정전에서 사용 불가)\r\n 1. 라운드시간을 8초로 조정하며 무릉도원이 펼쳐짐\r\n 2. 모든 플레이어를 마우가 위치로 스폰시킨 뒤 4초간 스턴상태 부여      "),
			Left, 2, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
	}
}

rule("[마우가] : 보조공격 - 넉백 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		마우가;
	}

	condition
	{
		Has Status(Victim, Burning) == True;
		Is Firing Primary(Event Player) == True;
	}

	action
	{
		Abort If Condition Is False;
		Apply Impulse(Victim, Position Of(Victim) - Position Of(Event Player), 3, To World, Cancel Contrary Motion);
	}
}

rule("[마우가] : 궁극기 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Is Using Ultimate(Players On Hero(Hero(마우가), All Teams)) == True;
		Global.RoundNumber != 420.690;
		Match Time <= 30;
	}

	action
	{
		Set Match Time(8);
		If(Event Player == Players On Hero(Hero(마우가), All Teams));
			Big Message(All Players(All Teams), Custom String("{0} 마우가 : 무릉도원에 온 것을 환영해!", Hero Icon String(Hero(마우가))));
			Wait(1, Ignore Condition);
			Press Button(Event Player, Button(Ultimate));
		Else;
			Teleport(Filtered Array(Event Player, Event Player.Z != 1), Position Of(Players On Hero(Hero(마우가), All Teams)) + Vector(0, 0.750,
				0));
			Set Status(Filtered Array(Event Player, Current Array Element != Players On Hero(Hero(마우가), All Teams)), Players On Hero(Hero(마우가),
				All Teams), Stunned, 4);
			Create Effect(All Players(All Teams), Cloud, Color(흰색), Position Of(Event Player), 16, None);
			Event Player.mauga_effect1 = Last Created Entity;
			Create Effect(All Players(All Teams), Cloud, Color(흰색), Position Of(Event Player) + Vector(0, 0, 5), 16, None);
			Event Player.mauga_effect2 = Last Created Entity;
			Create Effect(All Players(All Teams), Cloud, Color(Yellow), Position Of(Event Player), 12, None);
			Event Player.mauga_effect3 = Last Created Entity;
			Create Effect(All Players(All Teams), Cloud, Color(Yellow), Position Of(Event Player) + Vector(0, 0, 5), 12, None);
			Event Player.mauga_effect4 = Last Created Entity;
			Create Effect(All Players(All Teams), Cloud, Color(흰색), Position Of(Event Player), 8, None);
			Event Player.mauga_effect5 = Last Created Entity;
			Create Effect(All Players(All Teams), Cloud, Color(흰색), Position Of(Event Player) + Vector(0, 0, 5), 8, None);
			Event Player.mauga_effect6 = Last Created Entity;
			Create Effect(All Players(All Teams), Cloud, Color(Yellow), Position Of(Event Player), 4, None);
			Event Player.mauga_effect7 = Last Created Entity;
			Create Effect(All Players(All Teams), Cloud, Color(Yellow), Position Of(Event Player) + Vector(0, 0, 5), 4, None);
			Event Player.mauga_effect8 = Last Created Entity;
			Wait Until(Match Time == 0, 999);
			Destroy Effect(Event Player.mauga_effect1);
			Destroy Effect(Event Player.mauga_effect2);
			Destroy Effect(Event Player.mauga_effect3);
			Destroy Effect(Event Player.mauga_effect4);
			Destroy Effect(Event Player.mauga_effect5);
			Destroy Effect(Event Player.mauga_effect6);
			Destroy Effect(Event Player.mauga_effect7);
			Destroy Effect(Event Player.mauga_effect8);
		End;
	}
}

rule("[벤처] : 능력 설명 by KISUM *")
{
	event
	{
		Ongoing - Each Player;
		All;
		벤처;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 드릴 돌진", Ability Icon String(Hero(벤처), Button(Secondary Fire))), Null,
			Custom String(" 우클릭\r\n 앞으로 돌진해 적에게 넉백효과 부여                                   "), Left, 10, Color(Green), Color(흰색), Color(흰색),
			None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 9, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 잠복", Ability Icon String(Hero(벤처), Button(Ability 1))), Null, Custom String(
			" SHIFT\r\n 1. 땅 아래로 숨은 동안 일부 피해 면역 및 이동 속도가 1.5배가 됨\n 2. 사용 중 기본공격 사용 시 땅 위로 솟구쳐 오름"), Left, 8, Color(Green), Color(흰색),
			Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 슈퍼 벤처", Hero Icon String(Hero(벤처))), Null, Custom String(
			" Q (궁극기)\r\n 궁극기 사용 시간 동안 공격을 받은 적에게 1.5초간 넉다운 상태 부여"), Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 심장을 파드릴", Ability Icon String(Hero(벤처), Button(Melee))), Null, Custom String(
			" 근접공격 (궁극기 게이지 25%p 이상일때 사용 가능)\r\n 1. 근접공격에 맞은 적에게 넉백 및 잠깐의 스턴 효과 부여\r\n 2. 근접공격 성공시 피격횟수 X 4%p 만큼 궁극기 게이지 감소          "),
			Left, 2, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
	}
}

rule("[벤처] : 근접공격 허용 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		벤처;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Ultimate Charge Percent(Event Player) >= 25;
	}

	action
	{
		Set Melee Enabled(Event Player, True);
	}
}

rule("[벤처] : 근접공격 비허용 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		벤처;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Ultimate Charge Percent(Event Player) < 25;
	}

	action
	{
		Set Melee Enabled(Event Player, False);
	}
}

rule("[벤처] : 근접공격 - 넉백 + 스턴 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		벤처;
	}

	condition
	{
		Is Meleeing(Event Player) == True;
	}

	action
	{
		Abort If Condition Is False;
		Apply Impulse(Victim, Position Of(Victim) - Position Of(Event Player), 8, To World, Cancel Contrary Motion);
		Set Status(Victim, Null, Stunned, 0.200);
		Set Ultimate Charge(Event Player, Ultimate Charge Percent(Event Player) + -4);
	}
}

rule("[벤처] : 궁극기 - 넉다운 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		벤처;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Set Status(Victim, Null, Knocked Down, 1.500);
	}
}

rule("[벤처] : 잠복 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		벤처;
	}

	condition
	{
		Is Using Ability 1(Event Player) == True;
		Has Spawned(Event Player) == True;
	}

	action
	{
		Set Move Speed(Event Player, 180);
		Wait(0.500, Ignore Condition);
		Loop If(Is Using Ability 1(Event Player) == True);
		Set Move Speed(Event Player, 120);
	}
}

rule("[주노] : 능력 설명 by YaksuStn *")
{
	event
	{
		Ongoing - Each Player;
		All;
		주노;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 쁘띠 석양", Ability Icon String(Hero(주노), Button(Secondary Fire))), Null,
			Custom String(" 우클릭\r (4초 뒤 자동발사)\n 맞은 적에게 2.5초간 스턴상태 부여                                       "), Left, 10, Color(Green),
			Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 9, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} UFO", Ability Icon String(Hero(주노), Button(Ultimate))), Null, Custom String(
			" Q\n 주변 플레이어를 띄우는 광선 소환\r\n 높게 올라간 플레이어에게 3초간 넉다운상태 부여                          "), Left, 4, Color(Green), Color(흰색), Color(
			흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 3, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 대‍‍‍‍‍가‍‍‍‍‍리 슛", Ability Icon String(Hero(주노), Button(Melee))), Custom String(
			" 남은 쿨타임 {0}초", Event Player.J), Custom String(" 근접공격\r\n 근접공격에 맞은 적에게 1.5초간 넉다운상태 부여                  "), Left, 2, Color(
			Green), Color(Green), Color(흰색), Visible To Sort Order String and Color, Visible Never);
	}
}

rule("[주노] : 우클릭, 근접공격 by YaksuStn (투하이 != true 추가)")
{
	event
	{
		Player Dealt Damage;
		All;
		주노;
	}

	condition
	{
		Event Player.toohigh != True;
	}

	action
	{
		If(Event Player == Is Meleeing(Event Player));
			Small Message(Victim, Custom String("{0} 주노 : 대‍‍‍‍‍가‍‍‍‍‍리 슛!", Hero Icon String(Hero(주노))));
			Set Status(Victim, Null, Knocked Down, 1.500);
		Else;
			Small Message(Victim, Custom String("{0} 주노 : 개느려 ㅋㅋ", Hero Icon String(Hero(주노))));
			Set Status(Victim, Null, Stunned, 2.500);
	}
}

rule("[주노] : 근접공격 쿨타임 by YaksuStn")
{
	event
	{
		Ongoing - Each Player;
		All;
		주노;
	}

	condition
	{
		Is Button Held(Event Player, Button(Melee)) == True;
	}

	action
	{
		Event Player.J = 4;
		Wait(1, Ignore Condition);
		Event Player.J = 3;
		Wait(1, Ignore Condition);
		Event Player.J = 2;
		Wait(1, Ignore Condition);
		Event Player.J = 1;
		Wait(1, Ignore Condition);
		Event Player.J = 0;
	}
}

rule("[주노] : 근접공격 가능 by YaksuStn")
{
	event
	{
		Ongoing - Each Player;
		All;
		주노;
	}

	condition
	{
		Event Player.J == 0;
	}

	action
	{
		Allow Button(Event Player, Button(Melee));
	}
}

rule("[주노] : 근접공격 불가능 by YaksuStn")
{
	event
	{
		Ongoing - Each Player;
		All;
		주노;
	}

	condition
	{
		Event Player.J != 0;
	}

	action
	{
		Disallow Button(Event Player, Button(Melee));
	}
}

rule("[주노] : 궁극기 시전 by YaksuStn")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Is Using Ultimate(Players On Hero(Hero(주노), All Teams)) == True;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 주노 : UFO다!!", Hero Icon String(Hero(주노))));
		Start Facing(Players On Hero(Hero(주노), All Teams), Facing Direction Of(Players On Hero(Hero(주노), All Teams)), 1000, To World,
			None);
		Wait(0.500, Ignore Condition);
		Global.px = X Component Of(Position Of(Players On Hero(Hero(주노), All Teams)));
		Global.py = Y Component Of(Position Of(Players On Hero(Hero(주노), All Teams)));
		Global.pz = Z Component Of(Position Of(Players On Hero(Hero(주노), All Teams)));
		Global.jsinangle = Sine From Degrees(Horizontal Facing Angle Of(Players On Hero(Hero(주노), All Teams)));
		Global.cosangle = Cosine From Degrees(Horizontal Facing Angle Of(Players On Hero(Hero(주노), All Teams)));
		Wait(0.500, Ignore Condition);
		Stop Facing(Players On Hero(Hero(주노), All Teams));
		Abort If(Is Dead(Players On Hero(Hero(주노), All Teams)));
		Global.junoult_flag = True;
		Global.parameter = 4;
		Chase Global Variable Over Time(parameter, 23.500, 9, None);
		Wait(9, Ignore Condition);
		Global.junoult_flag = False;
	}
}

rule("[주노] : 궁극기 공중 부양 by YaksuStn")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.junoult_flag == True;
	}

	action
	{
		Global.junotarget = Filtered Array(All Players(All Teams), Distance Between(Vector(X Component Of(Position Of(
			Current Array Element)), 0, Z Component Of(Position Of(Current Array Element))), Vector(
			Global.px + Global.parameter * Global.jsinangle, 0, Global.pz + Global.parameter * Global.cosangle)) < 7);
		Apply Impulse(Filtered Array(Global.junotarget, Hero Of(Current Array Element) != Hero(주노)), Vector(0, 1, 0), 3, To World,
			Cancel Contrary Motion);
		Filtered Array(Global.junotarget, Altitude Of(Current Array Element) > 5).toohigh = True;
		Skip If(Match Time > 3, 1);
		Filtered Array(Global.junotarget, Hero Of(Current Array Element) != Hero(주노)).LASTDMGPLAYER = Players On Hero(Hero(주노), All Teams);
		Wait(0.016, Ignore Condition);
		Loop If Condition Is True;
	}
}

rule("[주노] : 궁극기 스턴 by YaksuStn")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Event Player.toohigh == True;
		Is On Ground(Event Player) == True;
		Hero Of(Event Player) != Hero(주노);
	}

	action
	{
		Event Player.toohigh = False;
		Set Status(Event Player, Null, Knocked Down, 3);
		Small Message(Event Player, Custom String("{0} 주노 : 너무 높이 올라간거 아니야? ㅋㅋ", Hero Icon String(Hero(주노))));
		If(Match Time < 3);
			Event Player.LASTDMGPLAYER = Players On Hero(Hero(주노), All Teams);
	}
}

rule("[해저드] : 능력 설명 by KISUM *")
{
	event
	{
		Ongoing - Each Player;
		All;
		해저드;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0}       불주사", Ability Icon String(Hero(해저드), Button(Secondary Fire))), Null,
			Custom String(" 우클릭\n 공격에 맞는 적에게 잠깐의 화상 효과 부여                              "), Left, 4, Color(Green), Color(흰색), Color(흰색),
			None, Visible Never);
	}
}

rule("[해저드] : 우클릭 by KISUM")
{
	event
	{
		Player Dealt Damage;
		All;
		해저드;
	}

	condition
	{
		Is Button Held(Event Player, Button(Secondary Fire)) == True;
	}

	action
	{
		Small Message(Victim, Custom String("{0} 해저드 : 따끔합니다!", Hero Icon String(Hero(해저드))));
		Set Status(Victim, Null, Burning, 1);
	}
}

rule("[프레야] : 능력 설명 by 큐브 *")
{
	event
	{
		Ongoing - Each Player;
		All;
		프레야;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create HUD Text(Event Player, Custom String("{0} 폭발 석궁", Ability Icon String(Hero(프레야), Button(Secondary Fire))), Null,
			Custom String(" 패시브\n 맞은 적들에게 넉백 부여             "), Left, 8, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 7, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 갈고리 사격", Ability Icon String(Hero(프레야), Button(Ultimate))), Null, Custom String(
			" 궁극기\n 맞은 적을 2초 뒤 자신의 위치로 불러옴"), Left, 4, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 차가운 돌진", Ability Icon String(Hero(프레야), Button(Ability 1))), Null, Custom String(
			" SHIFT\r\n 주변 적들에게 빙결 부여             "), Left, 6, Color(Green), Color(흰색), Color(흰색), None, Visible Never);
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 5, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
	}
}

rule("[프레야] : 패시브 by YaksuStn")
{
	event
	{
		Player Dealt Damage;
		All;
		프레야;
	}

	condition
	{
		Is Alive(Event Player) == True;
		Has Spawned(Event Player) == True;
	}

	action
	{
		Apply Impulse(Filtered Array(Victim, Victim != Event Player), Position Of(Victim) - Position Of(Event Player), 20, To World,
			Cancel Contrary Motion);
	}
}

rule("[프레야] : 궁극기 by YaksuStn")
{
	event
	{
		Player Dealt Damage;
		All;
		프레야;
	}

	condition
	{
		Is Alive(Event Player) == True;
		Has Spawned(Event Player) == True;
		Ultimate Charge Percent(Event Player) == 0;
	}

	action
	{
		Set Ultimate Charge(Players On Hero(Hero(프레야), All Teams), 1);
		Small Message(Event Player, Custom String("잡힌 플레이어: {1}{0}", Victim, Hero Icon String(Hero Of(Victim))));
		Wait(2, Ignore Condition);
		Teleport(Victim, Players On Hero(Hero(프레야), All Teams));
	}
}

rule("[프레야] : 프레야 좌클 사용 가능 불가능 by YaksuStn")
{
	event
	{
		Ongoing - Each Player;
		All;
		프레야;
	}

	condition
	{
		Is Alive(Event Player) == True;
		Has Spawned(Event Player) == True;
		Is Button Held(Event Player, Button(Secondary Fire)) == True;
	}

	action
	{
		Set Primary Fire Enabled(Event Player, True);
		Wait Until(Is Button Held(Event Player, Button(Secondary Fire)) == False, 100000000);
		Set Primary Fire Enabled(Event Player, False);
	}
}

rule("Blizz World All 맵(겨울 포함) 낙사 방지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		(Current Map == Map(블리자드 월드) || Current Map == Map(블리자드 월드 겨울)) == True;
		Y Component Of(Position Of(Event Player)) <= -6;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

rule("네크로폴리스 1번 맵 낙사 방지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(네크로폴리스);
		Global.ArenaID == 0;
		Y Component Of(Position Of(Event Player)) <= -12;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

rule("검은숲 2번 맵 낙사 방지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(검은 숲 겨울);
		Global.ArenaID == 1;
		Y Component Of(Position Of(Event Player)) <= 7;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

rule("네팔 성소 All 맵 낙사 방지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(네팔 성소);
		Y Component Of(Position Of(Event Player)) <= 120;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

disabled rule("도라도 1번 맵 낙사 방지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(도라도);
		Global.ArenaID == 1;
		Y Component Of(Position Of(Event Player)) <= 10;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

rule("리장 관제 센터 3번 맵 낙사 방지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(리장 관제 센터);
		Global.ArenaID == 2;
		Y Component Of(Position Of(Event Player)) <= 262;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

rule("리장 야시장 3번 맵 낙사 방지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(리장 야시장 설날);
		Global.ArenaID == 2;
		Y Component Of(Position Of(Event Player)) <= -8;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

rule("리장 정원 All 맵 낙사 방지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(리장 정원 설날);
		Y Component Of(Position Of(Event Player)) <= 89;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

rule("볼스카야 All 맵 낙사 방지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(볼스카야 인더스트리);
		Y Component Of(Position Of(Event Player)) <= -7.500;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

rule("샤토 기아르 2번 맵 낙사 방지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		(Current Map == Map(샤토 기야르) || Current Map == Map(샤토 기야르 할로윈)) == True;
		Global.ArenaID == 1;
		Y Component Of(Position Of(Event Player)) <= 1;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

rule("샤토 기야르 3번 맵 낙사 방지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(샤토 기야르);
		Global.ArenaID == 2;
		Y Component Of(Position Of(Event Player)) <= -0.500;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

rule("아이헨발데 2번 맵 낙사 방지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		(Current Map == Map(아이헨발데) || Current Map == Map(아이헨발데 할로윈)) == True;
		(Global.ArenaID == 1 || Global.ArenaID == 4) == True;
		Y Component Of(Position Of(Event Player)) <= 2;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

rule("오아시스 대학 1, 2번 맵 낙사 방지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(오아시스 대학);
		Y Component Of(Position Of(Event Player)) <= 7;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

rule("오아시스 정원 All 맵 낙사 방지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(오아시스 정원);
		Y Component Of(Position Of(Event Player)) <= 1;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

rule("왕의길 낙사 방지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(왕의 길 겨울);
		Y Component Of(Position Of(Event Player)) <= -10;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

rule("일리오스 우물 All 맵 낙사 방지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(일리오스 우물);
		Y Component Of(Position Of(Event Player)) <= -8;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

rule("카스티요 2번 맵 낙사 방지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(카스티요);
		Global.ArenaID == 1;
		Y Component Of(Position Of(Event Player)) <= 29;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

rule("페트라 1, 2, 4번 맵 낙사 방지 by KISUM (3 제외)")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(페트라);
		Global.ArenaID != 2;
		Y Component Of(Position Of(Event Player)) <= -16;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

rule("파리 4번 맵 낙사 주의 by KISUM")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Current Map == Map(파리);
		Global.ArenaID == 2;
	}

	action
	{
		Create HUD Text(All Players(All Teams), Custom String("{0} 낙사가 가능한 맵입니다! {0}", Icon String(Warning)), Null, Null, Right, -2, Color(
			Red), Color(흰색), Color(흰색), Visible To and String, Visible Always);
		Create HUD Text(All Players(All Teams), Null, Custom String("   "), Null, Right, -1, Color(Green), Color(Green), Color(흰색),
			Visible To and String, Visible Always);
	}
}

rule("페트라 3번 맵 낙사 주의 by KISUM")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Current Map == Map(페트라);
		Global.ArenaID == 2;
	}

	action
	{
		Create HUD Text(All Players(All Teams), Custom String("{0} 낙사가 가능한 맵입니다! {0}", Icon String(Warning)), Null, Null, Right, -2, Color(
			Red), Color(흰색), Color(흰색), Visible To and String, Visible Always);
		Create HUD Text(All Players(All Teams), Null, Custom String("   "), Null, Right, -1, Color(Green), Color(Green), Color(흰색),
			Visible To and String, Visible Always);
	}
}

rule("하나무라 2, 3번 맵 낙사 방지 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(하나무라);
		Y Component Of(Position Of(Event Player)) <= -7;
		(Global.ArenaID == 1 || Global.ArenaID == 2) == True;
	}

	action
	{
		Wait(0.016, Abort When False);
		Call Subroutine(OutsidePenalty);
	}
}

rule("워크샵 섬 theta 값 갱신 by Dote6")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		(Current Map == Map(워크샵 섬) || Current Map == Map(워크샵 섬 밤)) == True;
		(Global.NextRoundTrigger == 1 || Global.RoundNumber > 20) == True;
	}

	action
	{
		Stop Chasing Global Variable(theta);
		Global.theta = 0;
		If(Global.RoundNumber < 10);
			Chase Global Variable Over Time(theta, 1000 + 400 * Global.RoundNumber, 100, None);
		Else If(Global.RoundNumber <= 20);
			Chase Global Variable Over Time(theta, 5000, 100, Destination and Duration);
		Else;
			Chase Global Variable Over Time(theta, 10000, 100, Destination and Duration);
	}
}

rule("워크샵 그린 스크린(무궁화호) theta 값 갱신 by Dote6")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Current Map == Map(워크샵 그린 스크린);
		(Global.NextRoundTrigger == 1 || Global.RoundNumber > 20) == True;
		Global.ArenaID == 1;
	}

	action
	{
		Stop Chasing Global Variable(theta);
		Global.theta = Random Integer(-179, 180);
		If(Global.RoundNumber < 10);
			Chase Global Variable Over Time(theta, 1000 + 400 * Global.RoundNumber, 300, None);
		Else If(Global.RoundNumber <= 20);
			Chase Global Variable Over Time(theta, 5000, 300, Destination and Duration);
		Else;
			Chase Global Variable Over Time(theta, 10000, 300, Destination and Duration);
	}
}

rule("워크샵 그린 스크린(KTX) theta 값 갱신 by Dote6")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Current Map == Map(워크샵 그린 스크린);
		(Global.NextRoundTrigger == 1 || Global.RoundNumber > 20) == True;
		Global.ArenaID == 2;
	}

	action
	{
		Stop Chasing Global Variable(theta);
		Global.theta = Random Integer(-179, 180);
		If(Global.RoundNumber < 10);
			Chase Global Variable Over Time(theta, 1000 + 400 * Global.RoundNumber, 150, None);
		Else If(Global.RoundNumber <= 20);
			Chase Global Variable Over Time(theta, 5000, 150, Destination and Duration);
		Else;
			Chase Global Variable Over Time(theta, 10000, 150, Destination and Duration);
	}
}

rule("워크샵 섬 / 그린 스크린 0.07초 정답 셀 array 수정 Dote6")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		(Current Map == Map(워크샵 섬) || Current Map == Map(워크샵 섬 밤) || Current Map == Map(워크샵 그린 스크린)) == True;
		Match Time <= 0.070;
	}

	action
	{
		Global.stringPick = Empty Array;
		If(Global.Colours[0] == Global.CorrectColour);
			Global.stringPick = Append To Array(Global.stringPick, Global.SphereLocations[0]);
		End;
		If(Global.Colours[1] == Global.CorrectColour);
			Global.stringPick = Append To Array(Global.stringPick, Global.SphereLocations[1]);
		End;
		If(Global.Colours[2] == Global.CorrectColour);
			Global.stringPick = Append To Array(Global.stringPick, Global.SphereLocations[2]);
		End;
		If(Global.Colours[3] == Global.CorrectColour);
			Global.stringPick = Append To Array(Global.stringPick, Global.SphereLocations[3]);
		End;
		If(Global.Colours[4] == Global.CorrectColour);
			Global.stringPick = Append To Array(Global.stringPick, Global.SphereLocations[4]);
		End;
		If(Global.Colours[5] == Global.CorrectColour);
			Global.stringPick = Append To Array(Global.stringPick, Global.SphereLocations[5]);
		End;
	}
}

rule("워크샵 섬 / 그린 스크린 승자결정전 정답 셀 array 실시간 수정 Dote6")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		(Current Map == Map(워크샵 섬) || Current Map == Map(워크샵 섬 밤) || Current Map == Map(워크샵 그린 스크린)) == True;
		Global.RoundNumber > 100;
	}

	action
	{
		Global.stringPick = Empty Array;
		If(Global.Colours[0] == Global.CorrectColour);
			Global.stringPick = Append To Array(Global.stringPick, Global.SphereLocations[0]);
		End;
		If(Global.Colours[1] == Global.CorrectColour);
			Global.stringPick = Append To Array(Global.stringPick, Global.SphereLocations[1]);
		End;
		If(Global.Colours[2] == Global.CorrectColour);
			Global.stringPick = Append To Array(Global.stringPick, Global.SphereLocations[2]);
		End;
		If(Global.Colours[3] == Global.CorrectColour);
			Global.stringPick = Append To Array(Global.stringPick, Global.SphereLocations[3]);
		End;
		If(Global.Colours[4] == Global.CorrectColour);
			Global.stringPick = Append To Array(Global.stringPick, Global.SphereLocations[4]);
		End;
		If(Global.Colours[5] == Global.CorrectColour);
			Global.stringPick = Append To Array(Global.stringPick, Global.SphereLocations[5]);
		End;
		Wait(0.016, Ignore Condition);
		Loop;
	}
}

rule("워크샵 섬(낮) Spawnpoints by Dote6")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Current Map == Map(워크샵 섬);
	}

	action
	{
		Global.SphereLocations = Empty Array;
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(8.660, 0.300, 5));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(8.660, 0.300, -5));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0, 0.300, 10));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0, 0.300, -10));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(-8.660, 0.300, 5));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(-8.660, 0.300, -5));
		Create Effect(All Players(All Teams), Sphere, Color(흰색), Vector(0, 0.300, 0), 30, Visible To);
		Global.ArenaCentre = Vector(0, 0.300, 0);
		Global.ArenaRadius = 30;
		Create HUD Text(All Players(All Teams), Custom String("{0} 셀 위치가 계속 바뀝니다! {0}", Icon String(Warning)), Null, Null, Right, -2,
			Color(Red), Color(흰색), Color(흰색), Visible To and String, Visible Always);
		Create HUD Text(All Players(All Teams), Null, Custom String("   "), Null, Right, -1, Color(Green), Color(Green), Color(흰색),
			Visible To and String, Visible Always);
	}
}

rule("워크샵 섬(낮) spherelocation 값 갱신 by Dote6")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Current Map == Map(워크샵 섬);
	}

	action
	{
		Global.SphereLocations[0] = Vector(10 * Cosine From Degrees(Global.theta + 30), 0.300, 10 * Sine From Degrees(Global.theta + 30));
		Global.SphereLocations[1] = Vector(10 * Cosine From Degrees(Global.theta + -30), 0.300, 10 * Sine From Degrees(
			Global.theta + -30));
		Global.SphereLocations[2] = Vector(10 * Cosine From Degrees(Global.theta + 90), 0.300, 10 * Sine From Degrees(Global.theta + 90));
		Global.SphereLocations[3] = Vector(10 * Cosine From Degrees(Global.theta + -90), 0.300, 10 * Sine From Degrees(
			Global.theta + -90));
		Global.SphereLocations[4] = Vector(10 * Cosine From Degrees(Global.theta + 150), 0.300, 10 * Sine From Degrees(
			Global.theta + 150));
		Global.SphereLocations[5] = Vector(10 * Cosine From Degrees(Global.theta + -150), 0.300, 10 * Sine From Degrees(
			Global.theta + -150));
		Wait(0.016, Ignore Condition);
		Loop;
	}
}

rule("워크샵 섬(밤) Spawnpoints by Dote6")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Current Map == Map(워크샵 섬 밤);
	}

	action
	{
		Global.SphereLocations = Empty Array;
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(8.660, 5.300, 5));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(8.660, 5.300, -5));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0, 5.300, 10));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(0, 5.300, -10));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(-8.660, 5.300, 5));
		Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(-8.660, 5.300, -5));
		Create Effect(All Players(All Teams), Sphere, Color(흰색), Vector(0, 0.300, 0), 30, Visible To);
		Global.ArenaCentre = Vector(0, 0.300, 0);
		Global.ArenaRadius = 30;
		Create HUD Text(All Players(All Teams), Custom String("{0} 트리플 점프가 가능합니다! {0}", Icon String(Arrow: Up)), Null, Null, Right, -3.100,
			Color(Blue), Color(흰색), Color(흰색), Visible To and String, Visible Always);
		Create HUD Text(All Players(All Teams), Null, Custom String("   "), Null, Right, -3, Color(Green), Color(Green), Color(흰색),
			Visible To and String, Visible Always);
		Create HUD Text(All Players(All Teams), Custom String("{0} 셀 위치가 계속 바뀝니다! {0}", Icon String(Warning)), Null, Null, Right, -2,
			Color(Red), Color(흰색), Color(흰색), Visible To and String, Visible Always);
		Create HUD Text(All Players(All Teams), Null, Custom String("   "), Null, Right, -1, Color(Green), Color(Green), Color(흰색),
			Visible To and String, Visible Always);
	}
}

rule("워크샵 섬(밤) spherelocation 값 갱신 by Dote6")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Current Map == Map(워크샵 섬 밤);
	}

	action
	{
		Global.SphereLocations[0] = Vector(8.660, 5.300 + 5 * Sine From Degrees(Global.theta), 5);
		Global.SphereLocations[1] = Vector(8.660, 5.300 + 5 * Sine From Degrees(Global.theta + 60), -5);
		Global.SphereLocations[2] = Vector(0, 5.300 + 5 * Sine From Degrees(Global.theta + 120), 10);
		Global.SphereLocations[3] = Vector(0, 5.300 + 5 * Sine From Degrees(Global.theta + 180), -10);
		Global.SphereLocations[4] = Vector(-8.660, 5.300 + 5 * Sine From Degrees(Global.theta + 240), 5);
		Global.SphereLocations[5] = Vector(-8.660, 5.300 + 5 * Sine From Degrees(Global.theta + 300), -5);
		Wait(0.016, Ignore Condition);
		Loop;
	}
}

rule("워크샵 섬(밤) 더블트리플점프세팅 with Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(워크샵 섬 밤);
	}

	action
	{
		Event Player.Jump1 = 1;
	}
}

rule("워크샵 섬(밤) 더블트리플점프허용 with Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(워크샵 섬 밤);
		Altitude Of(Event Player) > 0.800;
		Is Button Held(Event Player, Button(Jump)) == False;
		Event Player.Jump1 > 0;
	}

	action
	{
		Event Player.Jump2 = 2;
	}
}

rule("워크샵 섬(밤)  더블점프 with Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(워크샵 섬 밤);
		Event Player.Jump2 == 2;
		Is Button Held(Event Player, Button(Jump)) == True;
	}

	action
	{
		Apply Impulse(Event Player, Up, 15, To World, Cancel Contrary Motion);
		Event Player.Jump1 = 0;
		Wait(0.250, Ignore Condition);
		Event Player.Jump2 = 3;
	}
}

rule("워크샵 섬(밤) 트리플점프 with Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(워크샵 섬 밤);
		Event Player.Jump2 == 3;
		Is Button Held(Event Player, Button(Jump)) == True;
	}

	action
	{
		Apply Impulse(Event Player, Up, 15, To World, Cancel Contrary Motion);
		Event Player.Jump1 = 0;
		Event Player.Jump2 = 0;
	}
}

rule("워크샵 섬(밤) 더블트리플점프비허용 with Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(워크샵 섬 밤);
		Is In Air(Event Player) != True;
	}

	action
	{
		Event Player.Jump1 = 1;
		Event Player.Jump2 = 0;
	}
}

rule("워크샵 그린 스크린 Spawnpoints by Dote6")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Current Map == Map(워크샵 그린 스크린);
	}

	action
	{
		"어차피 실시간으로 수정하니까 초기값은 의미 없을듯"
		Global.SphereLocations = Empty Array;
		Global.DynamicTrigger = 1;
		Global.ArenaID = Random Integer(1, 2);
		Wait(0.016, Ignore Condition);
		disabled Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(100, 0.300, 100));
		disabled Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(100, 0.300, 100));
		disabled Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(100, 0.300, 100));
		disabled Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(100, 0.300, 100));
		disabled Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(100, 0.300, 100));
		disabled Global.SphereLocations = Append To Array(Global.SphereLocations, Vector(100, 0.300, 100));
		Create Effect(All Players(All Teams), Sphere, Color(흰색), Vector(0, 0.300, 0), 45, Visible To);
		Global.ArenaCentre = Vector(0, 0.300, 0);
		Global.ArenaRadius = 45;
	}
}

rule("워크샵 그린 스크린 spherelocation 값 갱신 by Dote6")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Current Map == Map(워크샵 그린 스크린);
	}

	action
	{
		Global.SphereLocations[5] = Vector(30 * Cosine From Degrees(Global.theta + 0), 0.300, 30 * Sine From Degrees(Global.theta + 0));
		Global.SphereLocations[4] = Vector(30 * Cosine From Degrees(Global.theta + 11.478), 0.300, 30 * Sine From Degrees(
			Global.theta + 11.478));
		Global.SphereLocations[3] = Vector(30 * Cosine From Degrees(Global.theta + 22.957), 0.300, 30 * Sine From Degrees(
			Global.theta + 22.957));
		Global.SphereLocations[2] = Vector(30 * Cosine From Degrees(Global.theta + 34.435), 0.300, 30 * Sine From Degrees(
			Global.theta + 34.435));
		Global.SphereLocations[1] = Vector(30 * Cosine From Degrees(Global.theta + 45.913), 0.300, 30 * Sine From Degrees(
			Global.theta + 45.913));
		Global.SphereLocations[0] = Vector(30 * Cosine From Degrees(Global.theta + 57.392), 0.300, 30 * Sine From Degrees(
			Global.theta + 57.392));
		Wait(0.016, Ignore Condition);
		Loop;
	}
}

rule("워크샵 그린 스크린(KTX) 속도 증가 by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(워크샵 그린 스크린);
		Global.ArenaID == 2;
		Has Spawned(Event Player) == True;
		Event Player.on_train != 1;
		Event Player.on_train != 2;
	}

	action
	{
		Wait(0.100, Ignore Condition);
		For Player Variable(Event Player, cell_index, 0, Count Of(Global.SphereLocations), 1);
			If(Distance Between(Global.SphereLocations[Event Player.cell_index], Position Of(Event Player)) <= 5);
				Small Message(Event Player, Custom String("KTX 탑승!"));
				Set Move Speed(Event Player, 300);
				Event Player.on_train = 1;
			End;
		End;
		Loop If Condition Is True;
	}
}

rule("워크샵 그린 스크린(KTX) 속도 감소 by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(워크샵 그린 스크린);
		Global.ArenaID == 2;
		Event Player.on_train == 1;
	}

	action
	{
		Wait(0.500, Ignore Condition);
		For Player Variable(Event Player, cell_index, 0, Count Of(Global.SphereLocations), 1);
			If(Distance Between(Global.SphereLocations[Event Player.cell_index], Position Of(Event Player)) <= 5);
				Event Player.on_train = 2;
				Break;
			End;
		End;
		If(Event Player.on_train == 1);
			Event Player.on_train = 0;
			Small Message(Event Player, Custom String("KTX를 놓쳤어..."));
			If(Hero Of(Event Player) == Hero(루시우));
				If(Global.RoundNumber > 20);
					Set Move Speed(Event Player, 300);
				Else;
					Set Move Speed(Event Player, 111 + Global.RoundNumber * 9);
				End;
			Else;
				Set Move Speed(Event Player, 100);
			End;
		Else;
			Event Player.on_train = 1;
		End;
		Loop If Condition Is True;
	}
}

rule("워크샵 그린 스크린(KTX) theta 값 초기화 by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Current Map == Map(워크샵 그린 스크린);
		Global.ArenaID == 2;
		Match Time == 0;
	}

	action
	{
		Stop Chasing Global Variable(theta);
	}
}

rule("워크샵그린 스크린(무궁화호) 안내 by KISUM")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Current Map == Map(워크샵 그린 스크린);
		Global.ArenaID == 1;
	}

	action
	{
		Create HUD Text(All Players(All Teams), Custom String("{0} 무궁화호가 곧 떠납니다! {0}", Icon String(Flag)), Null, Null, Right, -2, Color(
			Sky Blue), Color(흰색), Color(흰색), Visible To and String, Visible Always);
		Create HUD Text(All Players(All Teams), Null, Custom String("   "), Null, Right, -1, Color(Green), Color(Green), Color(흰색),
			Visible To and String, Visible Always);
	}
}

rule("워크샵그린 스크린(KTX) 안내 by KISUM")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Current Map == Map(워크샵 그린 스크린);
		Global.ArenaID == 2;
	}

	action
	{
		Create HUD Text(All Players(All Teams), Custom String("{0} KTX를 타면 영웅도 빨라져요! {0}", Icon String(Bolt)), Null, Null, Right, -2,
			Color(Sky Blue), Color(흰색), Color(흰색), Visible To and String, Visible Always);
		Create HUD Text(All Players(All Teams), Null, Custom String("   "), Null, Right, -1, Color(Green), Color(Green), Color(흰색),
			Visible To and String, Visible Always);
	}
}

rule("[Mission] : 커플미션 발동 by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Custom String("{0}", Event Player) == Global.RANK;
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Is Button Held(Event Player, Button(Jump)) == True;
		Is Button Held(Event Player, Button(Crouch)) == True;
		Global.RoundNumber <= 1;
		Match Time >= 300;
	}

	action
	{
		Create HUD Text(All Players(All Teams), Custom String(""), Custom String("  "), Null, Right, 1.750, Color(Violet), Color(흰색),
			Color(흰색), Visible To and String, Default Visibility);
		Create HUD Text(All Players(All Teams), Custom String("♥ 커플 미션"), Custom String("커플끼리 제일 오래 살아남으세요!"), Null, Right, 1.800, Color(
			Violet), Color(흰색), Color(흰색), Visible To and String, Default Visibility);
		Create HUD Text(All Players(All Teams), Null, Custom String("   "), Null, Right, 1.850, Color(Green), Color(Green), Color(흰색),
			Visible To and String, Visible Never);
		Global.couple_list = All Living Players(All Teams);
		Global.couple_list = Randomized Array(Global.couple_list);
		If(Count Of(Global.couple_list) >= 2);
			Create HUD Text(All Players(All Teams), Null, Null, Custom String("{0}  {1}  {2}", Custom String("{0} {1}", Global.couple_list[0],
				Hero Icon String(Hero Of(Global.couple_list[0]))), Icon String(Heart), Custom String("{0} {1}", Global.couple_list[1],
				Hero Icon String(Hero Of(Global.couple_list[1])))), Right, 1.900, Color(흰색), Color(흰색), Color(Rose), Visible To and String,
				Default Visibility);
			Wait(0.016, Ignore Condition);
			Global.COUPLE_1 = Last Text ID;
		End;
		If(Count Of(Global.couple_list) >= 4);
			Create HUD Text(All Players(All Teams), Null, Null, Custom String("{0}  {1}  {2}", Custom String("{0} {1}", Global.couple_list[2],
				Hero Icon String(Hero Of(Global.couple_list[2]))), Icon String(Heart), Custom String("{0} {1}", Global.couple_list[3],
				Hero Icon String(Hero Of(Global.couple_list[3])))), Right, 1.910, Color(흰색), Color(흰색), Color(Rose), Visible To and String,
				Default Visibility);
			Wait(0.016, Ignore Condition);
			Global.COUPLE_2 = Last Text ID;
		End;
		If(Count Of(Global.couple_list) >= 6);
			Create HUD Text(All Players(All Teams), Null, Null, Custom String("{0}  {1}  {2}", Custom String("{0} {1}", Global.couple_list[4],
				Hero Icon String(Hero Of(Global.couple_list[4]))), Icon String(Heart), Custom String("{0} {1}", Global.couple_list[5],
				Hero Icon String(Hero Of(Global.couple_list[5])))), Right, 1.920, Color(흰색), Color(흰색), Color(Rose), Visible To and String,
				Default Visibility);
			Wait(0.016, Ignore Condition);
			Global.COUPLE_3 = Last Text ID;
		End;
		If(Count Of(Global.couple_list) >= 8);
			Create HUD Text(All Players(All Teams), Null, Null, Custom String("{0}  {1}  {2}", Custom String("{0} {1}", Global.couple_list[6],
				Hero Icon String(Hero Of(Global.couple_list[6]))), Icon String(Heart), Custom String("{0} {1}", Global.couple_list[7],
				Hero Icon String(Hero Of(Global.couple_list[7])))), Right, 1.940, Color(흰색), Color(흰색), Color(Rose), Visible To and String,
				Default Visibility);
			Wait(0.016, Ignore Condition);
			Global.COUPLE_4 = Last Text ID;
		End;
		If(Count Of(Global.couple_list) >= 10);
			Create HUD Text(All Players(All Teams), Null, Null, Custom String("{0}  {1}  {2}", Custom String("{0} {1}", Global.couple_list[8],
				Hero Icon String(Hero Of(Global.couple_list[8]))), Icon String(Heart), Custom String("{0} {1}", Global.couple_list[9],
				Hero Icon String(Hero Of(Global.couple_list[9])))), Right, 1.950, Color(흰색), Color(흰색), Color(Rose), Visible To and String,
				Default Visibility);
			Wait(0.016, Ignore Condition);
			Global.COUPLE_5 = Last Text ID;
		End;
		If(Count Of(Global.couple_list) == 12);
			Create HUD Text(All Players(All Teams), Null, Null, Custom String("{0}  {1}  {2}", Custom String("{0} {1}", Global.couple_list[10],
				Hero Icon String(Hero Of(Global.couple_list[10]))), Icon String(Heart), Custom String("{0} {1}", Global.couple_list[11],
				Hero Icon String(Hero Of(Global.couple_list[11])))), Right, 1.960, Color(흰색), Color(흰색), Color(Rose), Visible To and String,
				Default Visibility);
			Wait(0.016, Ignore Condition);
			Global.COUPLE_6 = Last Text ID;
		End;
		If(Count Of(Global.couple_list) % 2 != 0);
			Create HUD Text(All Players(All Teams), Null, Null, Custom String("나는 SOLO {2} {0} {1}", Global.couple_list[-1 + Count Of(
				Global.couple_list)], Hero Icon String(Hero Of(Global.couple_list[-1 + Count Of(Global.couple_list)])), Icon String(Skull)),
				Right, 1.970, Color(흰색), Color(흰색), Color(Red), Visible To and String, Default Visibility);
			Wait(0.016, Ignore Condition);
			Global.SOLO = Last Text ID;
		End;
		Create HUD Text(All Players(All Teams), Null, Custom String("   "), Null, Right, 1.980, Color(Green), Color(Green), Color(흰색),
			Visible To and String, Visible Never);
	}
}

rule("도움말 by KISUM")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Is Button Held(Event Player, Button(Secondary Fire)) == True;
		Is Button Held(Event Player, Button(Melee)) == True;
	}

	action
	{
		If(Event Player.howtoplay == 0);
			Create HUD Text(Event Player, Custom String(""), Custom String(""), Custom String(" \r\n \r\n \r\n{0}\r\n{1}\r\n{2}",
				Custom String(
				"{0} 기본 RULE                                       \r\n1. 각 라운드마다 우측 상단에 들어가야 할 셀의 색깔이 제시됩니다.\r\n2. 제한 시간이 0이 됐을 때 제시된 색깔 셀 안에 있어야",
				Hero Icon String(Hero(일리아리))), Custom String(
				"    다음 라운드로 진출할 수 있습니다.\r\n3. 영웅마다 가지고 있는 특별한 능력으로 자신을 보호하거나\r\n    상대를 방해할 수도 있습니다."), Custom String(
				"4. 마지막까지 살아남은 플레이어가 우승 플레이어가 됩니다.")), Top, 10, Color(Violet), Color(흰색), Color(Sky Blue), Visible To and String,
				Visible Never);
			Event Player.howtoplayV1 = Last Text ID;
			Create HUD Text(Event Player, Custom String(""), Custom String(""), Custom String(" \r\n{0}\r\n{1}\r\n{2}", Custom String(
				"{0} 패자부활전\r\n1. 한 라운드에 5명 이상 탈락할 경우 단 1회에 한하여 진행됩니다.\r\n2. 지정된 플레이어보다 먼저 셀에 들어갈 경우 패자부활에", Hero Icon String(Hero(키리코))),
				Custom String("    성공하여 다음 라운드로 진출할 수 있습니다.\r\n \r\n{0} 승자결정전", Hero Icon String(Hero(D.Va))), Custom String(
				"1. 모든 플레이어가 탈락하게 될 경우 승자결정전이 진행됩니다.\r\n2. 가장 먼저 셀에 들어가는 플레이어가 우승 플레이어가 됩니다.")), Top, 10, Color(Violet), Color(흰색), Color(
				Sky Blue), Visible To and String, Visible Never);
			Event Player.howtoplayV2 = Last Text ID;
			Event Player.howtoplay = 1;
		Else;
			Destroy HUD Text(Event Player.howtoplayV1);
			Destroy HUD Text(Event Player.howtoplayV2);
			Event Player.howtoplay = 0;
		End;
	}
}

rule("What a colorful world by Dote6")
{
	event
	{
		Ongoing - Global;
	}

	action
	{
		Chase Global Variable At Rate(colorchange, 100000000, 40, None);
	}
}

rule("[Sub] SombraHide")
{
	event
	{
		Subroutine;
		SombraHide;
	}

	action
	{
		Create HUD Text(All Living Players(All Teams), Custom String("{0} 솜브라에 의해 해킹되었습니다!", Ability Icon String(Hero(솜브라), Button(
			Ultimate))), Null, Null, Right, 0, Custom Color(255 * Absolute Value(Sine From Degrees(6 * Global.colorchange)),
			255 * Absolute Value(Sine From Degrees(10 * Global.colorchange)), 255 * Absolute Value(Sine From Degrees(
			2 * Global.colorchange)), 255), Null, Null, Color, Default Visibility);
		Global.HUDID = Last Text ID;
		Big Message(All Living Players(All Teams), Custom String("{0} : 어디 한 번 잘 찍어보시지 그래?", Hero Icon String(Hero(솜브라))));
	}
}

rule("[특전] 활성화 -> 좌클/우클 대기 (추가 by Dote6) // 건드리지 X")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	condition
	{
		Event Player.ttek_trigger == True;
		Global.RoundNumber < 10;
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Event Player.ttek_trigger = False;
		If(Global.KING != Event Player);
			Big Message(Event Player, Custom String("{0} 특전이 열렸습니다!", Icon String(Fire)));
		End;
		"공백용"
		Create HUD Text(Event Player, Custom String(""), Custom String(""), Custom String(
			" \r\n \r\n \r\n \r\n \r\n \r\n \r\n \r\n \r\n \r\n \r\n \r\n \r\n \r\n \r\n \r\n \r\n "), Top, 9.500, Color(Violet), Color(
			흰색), Color(Sky Blue), Visible To and String, Visible Never);
		Event Player.ttek_effect[0] = Last Text ID;
		"좌클릭 디스플레이"
		Create HUD Text(Event Player, Custom String(" {0} ", Input Binding String(Button(Primary Fire))), Event Player.ttek_text[0],
			Event Player.ttek_text[1], Top, 9.600, Color(Orange), Color(Orange), Color(흰색), Visible To and String, Visible Never);
		Event Player.ttek_effect[1] = Last Text ID;
		"공백용"
		Create HUD Text(Event Player, Custom String(""), Custom String(""), Custom String(" "), Top, 9.700, Color(Violet), Color(흰색),
			Color(Sky Blue), Visible To and String, Visible Never);
		Event Player.ttek_effect[2] = Last Text ID;
		"우클릭 디스플레이"
		Create HUD Text(Event Player, Custom String(" {0} ", Input Binding String(Button(Secondary Fire))), Event Player.ttek_text[2],
			Event Player.ttek_text[3], Top, 9.800, Color(Orange), Color(Orange), Color(흰색), Visible To and String, Visible Never);
		Event Player.ttek_effect[3] = Last Text ID;
		Start Rule(Ttek_LeftClick, Restart Rule);
		Start Rule(Ttek_RightClick, Restart Rule);
	}
}

rule("[특전] 좌클릭 시 (추가 by Dote6) // 건드리지 X")
{
	event
	{
		Subroutine;
		Ttek_LeftClick;
	}

	action
	{
		Wait Until(Is Button Held(Event Player, Button(Primary Fire)), 99999);
		Abort If(Event Player.ttek_effect == Null);
		Destroy HUD Text(Event Player.ttek_effect[0]);
		Destroy HUD Text(Event Player.ttek_effect[1]);
		Destroy HUD Text(Event Player.ttek_effect[2]);
		Destroy HUD Text(Event Player.ttek_effect[3]);
		Event Player.ttek_effect = Null;
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 30, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 특전", Icon String(Asterisk)), Null, Custom String(" {0} '{2}' 선택됨\r\n {1}",
			Input Binding String(Button(Primary Fire)), Event Player.ttek_text[1], Event Player.ttek_text[0]), Left, 31, Color(Orange),
			Color(흰색), Color(흰색), Visible To and String, Default Visibility);
		Event Player.ttek_left_enable = True;
	}
}

rule("[특전] 우클릭 시 (추가 by Dote6) // 건드리지 X")
{
	event
	{
		Subroutine;
		Ttek_RightClick;
	}

	action
	{
		Wait Until(Is Button Held(Event Player, Button(Secondary Fire)), 99999);
		Abort If(Event Player.ttek_effect == Null);
		Destroy HUD Text(Event Player.ttek_effect[0]);
		Destroy HUD Text(Event Player.ttek_effect[1]);
		Destroy HUD Text(Event Player.ttek_effect[2]);
		Destroy HUD Text(Event Player.ttek_effect[3]);
		Event Player.ttek_effect = Null;
		Create HUD Text(Event Player, Null, Custom String("   "), Null, Left, 30, Color(Green), Color(Green), Color(흰색), None,
			Visible Never);
		Create HUD Text(Event Player, Custom String("{0} 특전", Icon String(Asterisk)), Null, Custom String(" {0} '{2}' 선택됨\r\n {1}",
			Input Binding String(Button(Secondary Fire)), Event Player.ttek_text[3], Event Player.ttek_text[2]), Left, 31, Color(Orange),
			Color(흰색), Color(흰색), Visible To and String, Default Visibility);
		Event Player.ttek_right_enable = True;
	}
}

rule("[특전] 둠피스트 좌클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		둠피스트;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Global.DH += 3;
	}
}

rule("[특전] 둠피스트 우클릭")
{
	event
	{
		Player Dealt Damage;
		All;
		둠피스트;
	}

	condition
	{
		Is Using Ability 1(Event Player) == True;
		Event Player.ttek_right_enable == True;
	}

	action
	{
		Wait Until(Is In Air(Event Player) == False, 99999);
		Set Status(Victim, Null, Knocked Down, 1.250);
	}
}

rule("[특전] 마우가 좌클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		마우가;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Set Ability 2 Enabled(Event Player, True);
	}
}

rule("[특전] 마우가 좌클릭 화상 상태 부여")
{
	event
	{
		Ongoing - Each Player;
		All;
		마우가;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Using Ability 2(Event Player) == True;
	}

	action
	{
		Event Player.M = Players Within Radius(Event Player, 10, Opposite Team Of(Team Of(Event Player)), Surfaces);
		Event Player.M = Filtered Array(Event Player.M, Current Array Element != Event Player);
		Set Status(Event Player.M, Event Player, Burning, 3);
	}
}

rule("[특전] 우클릭 마우가")
{
	event
	{
		Player Dealt Damage;
		All;
		마우가;
	}

	condition
	{
		Is Using Ability 1(Event Player) == True;
		Event Player.ttek_right_enable == True;
	}

	action
	{
		Set Status(Victim, Null, Knocked Down, 1.500);
		Small Message(Victim, Custom String("{0} 마우가 : 빡쳐?", Hero Icon String(Hero(마우가))));
	}
}

rule("[특전] 라마트라 좌클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		라마트라;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Set Ability 2 Enabled(Event Player, True);
	}
}

rule("[특전] 라마트라 좌클릭 - 소용돌이 스턴 (by 누구인)")
{
	event
	{
		Player Dealt Damage;
		All;
		라마트라;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Is Using Ultimate(Event Player) == False;
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Set Status(Victim, Null, Stunned, 0.750);
	}
}

rule("[특전] 라마트라 우클릭")
{
	event
	{
		Player Dealt Damage;
		All;
		라마트라;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
		Event Player.ttek_right_enable == True;
	}

	action
	{
		Set Status(Victim, Null, Burning, 0.750);
	}
}

rule("[특전] 로드호그 좌클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		로드호그;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Set Secondary Fire Enabled(Event Player, True);
	}
}

rule("[특전] 로드호그 좌클릭 - 신속의 물약 (by 누구인)")
{
	event
	{
		Ongoing - Each Player;
		All;
		로드호그;
	}

	condition
	{
		Is Alive(Event Player) == True;
		Event Player.Z != 1;
		Is Firing Secondary(Event Player) == True;
	}

	action
	{
		Set Move Speed(Event Player, 240);
		Wait Until(Is Firing Secondary(Event Player) == False, 99999);
		Set Move Speed(Event Player, 120);
	}
}

rule("[특전] 로드호그 우클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		로드호그;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
	}

	action
	{
		Event Player.HOG1 += 5;
	}
}

rule("[특전] 라인하르트 좌클릭")
{
	event
	{
		Player Dealt Damage;
		All;
		라인하르트;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Firing Primary(Event Player) == True;
	}

	action
	{
		Set Status(Victim, Null, Burning, 1.500);
	}
}

rule("[특전] 라인하르트 우클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		라인하르트;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
	}

	action
	{
		Set Ability 2 Enabled(Event Player, True);
	}
}

rule("[특전] 라인하르트 우클릭 - 화상 상태 부여 by 누구인")
{
	event
	{
		Player Dealt Damage;
		All;
		라인하르트;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Is Firing Primary(Event Player) == False;
		Is Using Ability 1(Event Player) == False;
		Is Using Ultimate(Event Player) == False;
	}

	action
	{
		Set Status(Victim, Null, Burning, 3);
	}
}

rule("[특전] 해저드 좌클릭")
{
	event
	{
		Player Dealt Damage;
		All;
		해저드;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Button Held(Event Player, Button(Secondary Fire)) == True;
	}

	action
	{
		Abort If Condition Is False;
		Apply Impulse(Victim, Position Of(Victim) - Position Of(Event Player), 3.500, To World, Cancel Contrary Motion);
	}
}

rule("[특전] 해저드 우클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		해저드;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 해저드 : 다 찢어버려!!!!!!", Hero Icon String(Hero(해저드))));
		Wait(0.890, Ignore Condition);
		Set Status(Filtered Array(All Players(All Teams), Current Array Element != Event Player), Event Player, Hacked, 2.500);
		Set Status(Filtered Array(All Players(All Teams), Current Array Element != Event Player), Event Player, Rooted, 2.500);
	}
}

rule("[특전] 레킹볼 좌클릭 - Chase Player Variable로 수정 by Dote6**")
{
	event
	{
		Ongoing - Each Player;
		All;
		레킹볼;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Button Held(Event Player, Button(Interact)) == True;
		Event Player.WRF == 0;
		Is Alive(Event Player) == True;
	}

	action
	{
		Apply Impulse(Event Player, Vector(0, 2, 0), 40, To Player, Cancel Contrary Motion);
		Event Player.WRF = 30;
		Chase Player Variable Over Time(Event Player, WRF, 0, 30, None);
	}
}

rule("[특전] 레킹볼 좌클릭 - 게이지 표시, 올림으로 수정 by Dote6**")
{
	event
	{
		Ongoing - Each Player;
		All;
		레킹볼;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Create Progress Bar HUD Text(Players On Hero(Hero(레킹볼), All Teams), 3.333 * Event Player.WRF, Custom String("잔상 남은 쿨타임 : {0}초",
			Round To Integer(Event Player.WRF, Up)), Left, 33, Color(Orange), Color(흰색), Visible To and Values, Visible Never);
	}
}

rule("[특전] 레킹볼 좌클릭 - 상호작용 사용 가능 메세지")
{
	event
	{
		Ongoing - Each Player;
		All;
		레킹볼;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Event Player.WRF == 0;
	}

	action
	{
		Small Message(Players On Hero(Hero(레킹볼), All Teams), Custom String("상호작용 사용가능"));
	}
}

rule("[특전] 레킹볼 우클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		레킹볼;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Using Ability 2(Event Player) == True;
	}

	action
	{
		Set Status(Event Player, Event Player, Invincible, 6.667);
	}
}

rule("[특전] 시그마 좌클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		시그마;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Button Held(Event Player, Button(Jump)) == True;
	}

	action
	{
		Apply Impulse(Event Player, Vector(0, 1, 0), 5, To Player, Cancel Contrary Motion);
		Wait(0.200, Ignore Condition);
		Loop If Condition Is True;
	}
}

rule("[특전] 시그마 좌클릭 : 이동속도 제한")
{
	event
	{
		Ongoing - Each Player;
		All;
		시그마;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is In Air(Event Player) == True;
	}

	action
	{
		Set Move Speed(Event Player, 80);
		Wait Until(Is In Air(Event Player) == False, 99999);
		Set Move Speed(Event Player, 120);
	}
}

rule("[특전] 시그마 우클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		시그마;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 시그마 : 지구가! 너희에게 노래하고 있어!!", Hero Icon String(Hero(시그마))));
		Damage(All Living Players(All Teams), Event Player, 100);
		Apply Impulse(Filtered Array(All Living Players(All Teams), Current Array Element != Event Player), Vector(0, -3, 0), 15,
			To Player, Cancel Contrary Motion);
		Wait(1.600, Ignore Condition);
		Set Status(Filtered Array(All Living Players(All Teams), Current Array Element != Event Player), Null, Knocked Down, 1.400);
	}
}

rule("[특전] 오리사 좌클릭 1")
{
	event
	{
		Ongoing - Each Player;
		All;
		오리사;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Ability Cooldown(Event Player, Button(Secondary Fire)) > 0;
	}

	action
	{
		Set Ability Cooldown(Event Player, Button(Secondary Fire), Ability Cooldown(Event Player, Button(Secondary Fire)) / 1.428);
	}
}

rule("[특전] 오리사 좌클릭 2")
{
	event
	{
		Ongoing - Each Player;
		All;
		오리사;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Ability Cooldown(Event Player, Button(Ability 2)) > 0;
	}

	action
	{
		Set Ability Cooldown(Event Player, Button(Ability 2), Ability Cooldown(Event Player, Button(Ability 2)) / 1.428);
	}
}

rule("[특전] 오리사 우클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		오리사;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
	}

	action
	{
		Set Ultimate Ability Enabled(Event Player, True);
		Set Ultimate Charge(Event Player, 100);
	}
}

rule("[특전] 오리사 우클릭 - 궁극기 사용 중 무적")
{
	event
	{
		Ongoing - Each Player;
		All;
		오리사;
	}

	condition
	{
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Set Status(Event Player, Null, Unkillable, 9999);
		Wait Until(!Is Using Ultimate(Event Player), 99999);
		Clear Status(Event Player, Unkillable);
		Set Ultimate Charge(Event Player, 0);
		Set Ultimate Ability Enabled(Event Player, False);
		Disallow Button(Event Player, Button(Ultimate));
	}
}

rule("[특전] 자리야 좌클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		자리야;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Start Scaling Player(Event Player, 0.334, True);
	}
}

rule("[특전] 자리야 우클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		자리야;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
	}

	action
	{
		Set Gravity(Event Player, 90);
	}
}

rule("[특전] 정커퀸 좌클릭 by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		정커퀸;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Set Melee Enabled(Event Player, True);
	}
}

rule("[특전] 정커퀸 좌클릭 - 근접공격 쿨타임 by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		정커퀸;
	}

	condition
	{
		Is Meleeing(Event Player) == True;
	}

	action
	{
		Set Melee Enabled(Event Player, False);
		Event Player.WRF = 3;
		Chase Player Variable Over Time(Event Player, WRF, 0, 3, None);
		Wait(3, Ignore Condition);
		Set Melee Enabled(Event Player, True);
	}
}

rule("[특전] 정커퀸 좌클릭 - 근접공격 쿨타임 게이지 표시 by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		정커퀸;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Create Progress Bar HUD Text(Players On Hero(Hero(정커퀸), All Teams), 33.333 * Event Player.WRF, Custom String("근접공격 남은 쿨타임 : {0}초",
			Round To Integer(Event Player.WRF, Up)), Left, 33, Color(Orange), Color(흰색), Visible To and Values, Visible Never);
	}
}

rule("[특전] 정커퀸 우클릭 기본 by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		정커퀸;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
	}

	action
	{
		Set Status(Event Player, Null, Hacked, 0.010);
		Set Ability 2 Enabled(Event Player, False);
		Set Ability Cooldown(Event Player, Button(Secondary Fire), 3);
		Destroy HUD Text(Event Player.queen_var[8]);
		Wait(0.016, Ignore Condition);
		Create HUD Text(Event Player, Custom String("{0} 입체기동 톱니칼 II", Ability Icon String(Hero(정커퀸), Button(Secondary Fire))), Null,
			Custom String(" 특전 준비중...\n ({0}초 뒤 활성화)", Evaluate Once(Total Time Elapsed) + 3 - Total Time Elapsed), Left, 8, Color(Green),
			Color(흰색), Color(흰색), String, Visible Never);
		Event Player.queen_var[8] = Last Text ID;
		Wait(3, Ignore Condition);
		Destroy HUD Text(Event Player.queen_var[8]);
		Wait(0.016, Ignore Condition);
		Create HUD Text(Event Player, Custom String("{0} 입체기동 톱니칼 II", Ability Icon String(Hero(정커퀸), Button(Secondary Fire))), Null,
			Custom String(" 우클릭(0.2~2초 사이 홀드) → 떼기\n 톱니칼 위치로 순간이동                "), Left, 8, Color(Green), Color(흰색), Color(흰색), None,
			Visible Never);
		Create Progress Bar HUD Text(Event Player, 50 * Event Player.queen_time, Custom String("우클릭 누른 시간: {0}초", Event Player.queen_time),
			Left, 50, Event Player.queen_var[14], Color(Orange), Visible To Values and Color, Default Visibility);
	}
}

rule("[특전] 정커퀸 우클릭 칼위치 계산 by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		정커퀸;
	}

	condition
	{
		Is Firing Secondary(Event Player) == True;
		Event Player.ttek_right_enable == True;
	}

	action
	{
		"progress bar 용"
		Event Player.queen_time = 0;
		Chase Player Variable At Rate(Event Player, queen_time, 2, 1, Destination and Rate);
		"종료조건 체크하는 subroutine"
		Start Rule(QUEEN_END_COND, Restart Rule);
		"progress bar 색깔 관리하는 subroutine"
		Start Rule(QUEEN_COL_CNG, Restart Rule);
		"퀸이 칼 맞춘 적"
		Event Player.queen_var[15] = Null;
		"지형지물에 닿으면 좌표가 됨 (default: 0)"
		Event Player.queen_var[12] = 0;
		"투사체 속도"
		Event Player.queen_var[1] = 35;
		"delta 보정 (원래는 0.02->0.015)"
		Event Player.queen_var[2] = 0.015;
		"칼은 최대 2초"
		Event Player.queen_var[3] = 2;
		"중력가속도"
		Event Player.queen_var[0] = -8.500;
		"베지어 곡선: p0"
		Event Player.queen_var[4] = Eye Position(Event Player);
		"바라보는 방향"
		Event Player.queen_var[7] = Vertical Facing Angle Of(Event Player) < -89 ? Up : (Vertical Facing Angle Of(Event Player)
			> 89 ? Down : Normalize(Facing Direction Of(Event Player) + Event Player.queen_var[2] * Up));
		"베지어 곡선: p1"
		Event Player.queen_var[5] = Event Player.queen_var[4] + 0.500 * Event Player.queen_var[1] * Event Player.queen_var[3] * Event Player.queen_var[7];
		"베지어 곡선: p2"
		Event Player.queen_var[6] = Event Player.queen_var[4] + Event Player.queen_var[1] * Event Player.queen_var[3] * Event Player.queen_var[7] + 0.500 * Event Player.queen_var[3] * Event Player.queen_var[3] * Event Player.queen_var[0] * Up;
		For Player Variable(Event Player, queen_t, 0, 2, 0.016);
			Skip If(Event Player.queen_t % 0.048 != 0, 1);
			Wait(0.016, Ignore Condition);
			Event Player.queen_var[9] = Evaluate Once((1 - Event Player.queen_t) * (1 - Event Player.queen_t))
				* Event Player.queen_var[4] + Evaluate Once(2 * (1 - Event Player.queen_t) * Event Player.queen_t)
				* Event Player.queen_var[5] + Evaluate Once(Event Player.queen_t * Event Player.queen_t) * Event Player.queen_var[6];
			Event Player.queen_var[10] = Evaluate Once((0.984 - Event Player.queen_t) * (0.984 - Event Player.queen_t))
				* Event Player.queen_var[4] + Evaluate Once(2 * (0.984 - Event Player.queen_t) * (Event Player.queen_t + 0.016))
				* Event Player.queen_var[5] + Evaluate Once((Event Player.queen_t + 0.016) * (Event Player.queen_t + 0.016))
				* Event Player.queen_var[6];
			Event Player.queen_var[11] = Ray Cast Hit Position(Event Player.queen_var[9], Event Player.queen_var[10], Null, Event Player,
				True);
			"지형지물 닿음"
			If(Event Player.queen_var[11] != Event Player.queen_var[10]);
				Event Player.queen_var[12] = Event Player.queen_var[11];
				Break;
			End;
			Wait(0.016, Ignore Condition);
		End;
	}
}

rule("[특전] 정커퀸 우클릭 칼떼면 이동 by Dote6")
{
	event
	{
		Subroutine;
		QUEEN_END_COND;
	}

	action
	{
		"우클 뗄때까지 대기"
		Wait Until(!Is Button Held(Event Player, Button(Secondary Fire)), 99999);
		Stop Chasing Player Variable(Event Player, queen_time);
		"0.2초 이하 2초 이상이면 실행X"
		Abort If(Event Player.queen_time <= 0.200 || Event Player.queen_time >= 2);
		"칼에 맞은 적이 퀸과 부딪히지 않게 함"
		Set Status(Event Player, Null, Phased Out, 0.500);
		"칼이 적에 닿음"
		If(Event Player.queen_var[15] != Null);
			Teleport(Event Player, Position Of(Event Player.queen_var[15]) + 0.500 * Normalize(Position Of(Event Player) - Position Of(
				Event Player.queen_var[15])));
		"칼이 벽에 안닿음"
		Else If(Event Player.queen_var[12] == 0);
			Teleport(Event Player, Event Player.queen_var[9] + 0.500 * Normalize(Position Of(Event Player) - Event Player.queen_var[9]));
		"칼이 벽에 닿음"
		Else;
			Teleport(Event Player, Event Player.queen_var[12] + 0.500 * Normalize(Position Of(Event Player) - Event Player.queen_var[12]));
		End;
		"칼 회수"
		Press Button(Event Player, Button(Secondary Fire));
		"씹힘 방지"
		Wait(0.100, Ignore Condition);
		Press Button(Event Player, Button(Secondary Fire));
	}
}

rule("[특전] 정커퀸 우클릭 progress bar 색깔 by Dote6")
{
	event
	{
		Subroutine;
		QUEEN_COL_CNG;
	}

	action
	{
		Event Player.queen_var[14] = Color(Red);
		Wait(0.200, Ignore Condition);
		Abort If(Event Player.queen_time <= 0.200);
		Event Player.queen_var[14] = Color(Green);
		Wait(1.800, Ignore Condition);
		Abort If(Event Player.queen_time < 2);
		Event Player.queen_var[14] = Color(Red);
		Wait Until(Ability Cooldown(Event Player, Button(Secondary Fire)) == 0, 99999);
		Event Player.queen_time = 0;
	}
}

rule("[특전] 정커퀸 우클릭 맞춘 적 저장 by Dote6")
{
	event
	{
		Player Dealt Damage;
		All;
		정커퀸;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
	}

	action
	{
		Event Player.queen_var[15] = Victim;
	}
}

rule("[특전] 정커퀸 우클릭 쿨타임 50% 감소 by Dote6")
{
	event
	{
		Ongoing - Each Player;
		All;
		정커퀸;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Ability Cooldown(Event Player, Button(Secondary Fire)) > 6;
	}

	action
	{
		Set Ability Cooldown(Event Player, Button(Secondary Fire), 6);
	}
}

rule("[특전] D.VA 좌클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		D.Va;
	}

	condition
	{
		Is In Alternate Form(Event Player) == True;
		Event Player.hana_count == 1;
		Is Firing Primary(Event Player) == True;
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Set Status(Event Player, Null, Stunned, 0.250);
	}
}

rule("[특전] D.VA 우클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		D.Va;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Event Player.hana_count == 1;
	}

	action
	{
		Event Player.HANA1 = Event Player.HANA1 + 5;
	}
}

rule("윈스턴 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		윈스턴;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Set Primary Fire Enabled(Event Player, True);
		Set Max Ammo(Event Player, 0, 20);
		Set Ammo(Event Player, 0, 20);
	}
}

rule("윈스턴 좌클")
{
	event
	{
		Player Dealt Damage;
		All;
		윈스턴;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Firing Primary(Event Player) == True;
	}

	action
	{
		Set Status(Victim, Event Player, Stunned, 0.500);
		Wait(0.500, Ignore Condition);
	}
}

rule("윈스턴 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		윈스턴;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Set Ability Cooldown(Event Player, Button(Ability 1), 15);
	}
}

rule("윈스턴 우클")
{
	event
	{
		Player Dealt Damage;
		All;
		윈스턴;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Using Ultimate(Event Player) != True;
	}

	action
	{
		Set Status(Victim, Event Player, Knocked Down, 2);
	}
}

rule("라이프위버 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		라이프위버;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Wait(1.750, Ignore Condition);
		Set Ultimate Charge(Event Player, Ultimate Charge Percent(Event Player) + 6);
		Wait(1.750, Ignore Condition);
		Set Ultimate Charge(Event Player, Ultimate Charge Percent(Event Player) + 6);
		Wait(1.750, Ignore Condition);
		Set Ultimate Charge(Event Player, Ultimate Charge Percent(Event Player) + 6);
		Wait(1.750, Ignore Condition);
		Set Ultimate Charge(Event Player, Ultimate Charge Percent(Event Player) + 6);
		Wait(1.750, Ignore Condition);
		Set Ultimate Charge(Event Player, Ultimate Charge Percent(Event Player) + 6);
		Wait(1.750, Ignore Condition);
		Set Ultimate Charge(Event Player, Ultimate Charge Percent(Event Player) + 6);
		Wait(1.750, Ignore Condition);
		Set Ultimate Charge(Event Player, Ultimate Charge Percent(Event Player) + 6);
		Wait(1.750, Ignore Condition);
		Set Ultimate Charge(Event Player, Ultimate Charge Percent(Event Player) + 6);
		Wait(1.750, Ignore Condition);
		Set Ultimate Charge(Event Player, Ultimate Charge Percent(Event Player) + 6);
	}
}

rule("라이프위버 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		라이프위버;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Ability Cooldown(Event Player, Button(Ability 1)) > 15;
	}

	action
	{
		Set Ability Cooldown(Event Player, Button(Ability 1), 15);
	}
}

rule("루시우 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		루시우;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Button Held(Event Player, Button(Ability 1)) == True;
	}

	action
	{
		Set Move Speed(Event Player, 300);
		Wait(0.100, Ignore Condition);
		Set Move Speed(Event Player, 111 + Global.RoundNumber * 9);
	}
}

rule("루시우 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		루시우;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Wait(0.700, Ignore Condition);
		Wait Until(Is In Air(Event Player) == False, 99999);
		Event Player.M = Players Within Radius(Event Player, 12, Opposite Team Of(Team Of(Event Player)), Surfaces);
		Event Player.M = Filtered Array(Event Player.M, Current Array Element != Event Player);
		Damage(Filtered Array(Event Player.M, Current Array Element != Event Player), Event Player, 100);
		Set Status(Event Player.M, Event Player, Knocked Down, 3);
	}
}

rule("메르시 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		메르시;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Global.MRSO += 1;
	}
}

rule("메르시 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		메르시;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
	}

	action
	{
		Event Player.MER = Random Integer(1, 20);
		Set Melee Enabled(Event Player, True);
	}
}

rule("모이라 좌클 특전 효과")
{
	event
	{
		Player Dealt Damage;
		All;
		모이라;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Alive(Event Player) == True;
		Is Using Ability 1(Event Player) == False;
	}

	action
	{
		Wait(0.150, Ignore Condition);
		Set Status(Victim, Event Player, Frozen, 0.300);
	}
}

rule("모이라 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		모이라;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Using Ability 2(Event Player) == True;
	}

	action
	{
		Wait Until(Is Using Ability 2(Event Player) != True, 99999);
		Abort If(Ability Cooldown(Event Player, Button(Ability 2)) == 0);
		Event Player.M = Random Integer(1, 2);
		If(Event Player.M == 1);
			Set Ability Cooldown(Event Player, Button(Ability 2), 0);
	}
}

rule("[특전] 바티스트 좌클릭 (추가 by Dote6)")
{
	event
	{
		Ongoing - Each Player;
		All;
		바티스트;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Event Player.aim_vector_ += 0.090 * Normalize(First Of(Sorted Array(Global.LivingPlayers, Distance Between(
			Event Player.aim_vector_, Current Array Element))) - Event Player.aim_vector_);
		Event Player.left_end_ = Event Player.aim_vector_ + Event Player.unit_vector_ * 2;
		Event Player.right_end_ = Event Player.aim_vector_ + Event Player.unit_vector_ * -2;
		Wait(0.030, Ignore Condition);
		Loop If Condition Is True;
	}
}

rule("[특전] 바티스트 우클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		바티스트;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
	}

	action
	{
		Global.door_count += 300;
	}
}

rule("브리기테 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		브리기테;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Using Ultimate(Event Player) != True;
		Is Button Held(Event Player, Button(Ability 2)) == True;
		Ability Charge(Event Player, Button(Ability 2)) > 0;
	}

	action
	{
		Set Ability Charge(Event Player, Button(Ability 2), Ability Charge(Event Player, Button(Ability 2)) + -1);
		Set Status(Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams)
			!= Is Dead(Player Closest To Reticle(Event Player, All Teams))), Event Player, Frozen, 0.300);
		Small Message(Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams)
			!= Is Dead(Player Closest To Reticle(Event Player, All Teams))), Custom String("{0} 브리기테 : 내 쿨팩 받아줘!", Hero Icon String(Hero(
			브리기테))));
	}
}

rule("브리기테 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		브리기테;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
	}

	action
	{
		Start Scaling Barriers(Event Player, 4, True);
	}
}

rule("[특전] 아나 좌클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		아나;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Ability Cooldown(Event Player, Button(Ability 1)) > 0;
	}

	action
	{
		Set Ability Cooldown(Event Player, Button(Ability 1), Ability Cooldown(Event Player, Button(Ability 1)) / 2);
	}
}

rule("[특전] 아나 우클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		아나;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Set Move Speed(Event Player, 200);
		Wait Until(Is Using Ultimate(Event Player) == False, 99999);
		Set Move Speed(Event Player, 120);
	}
}

rule("[특전] 일리아리 좌클릭")
{
	event
	{
		Player Dealt Damage;
		All;
		일리아리;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Event Was Critical Hit == True;
	}

	action
	{
		Set Ability Cooldown(Event Player, Button(Ability 1), Ability Cooldown(Event Player, Button(Ability 1)) / 2);
	}
}

rule("[특전] 일리아리 우클릭")
{
	event
	{
		Player Dealt Damage;
		All;
		일리아리;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Event Was Critical Hit == True;
	}

	action
	{
		Set Ultimate Charge(Event Player, Ultimate Charge Percent(Event Player) * 2);
	}
}

rule("젠야타 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		젠야타;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Wait(0.100, Ignore Condition);
		Clear Status(Event Player, Rooted);
	}
}

rule("젠야타 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		젠야타;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
	}

	action
	{
		Event Player.ZYTGAGE += 40;
	}
}

rule("주노 좌클 특전 효과")
{
	event
	{
		Player Dealt Damage;
		All;
		주노;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Meleeing(Event Player) != True;
		Event Player.toohigh != True;
	}

	action
	{
		Set Status(Victim, Event Player, Stunned, 5);
	}
}

rule("주노 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		주노;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Using Ability 2(Event Player) == True;
	}

	action
	{
		Set Move Speed(Event Player, Random Integer(240, 360));
		Wait(6.540, Ignore Condition);
		Set Move Speed(Event Player, 120);
	}
}

rule("키리코 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		키리코;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Button Held(Event Player, Button(Ability 1)) == True;
		Is Using Ultimate(Event Player) != True;
		Has Status(Event Player, Hacked) == False;
		Has Status(Event Player, Knocked Down) == False;
		Has Status(Event Player, Asleep) == False;
		Has Status(Event Player, Frozen) == False;
		Has Status(Event Player, Rooted) == False;
		Has Status(Event Player, Stunned) == False;
		Is In View Angle(Event Player, Player Closest To Reticle(Event Player, All Teams), 90) == True;
	}

	action
	{
		Filtered Array(Player Closest To Reticle(Event Player, All Teams), Player Closest To Reticle(Event Player, All Teams) == Is Dead(
			Player Closest To Reticle(Event Player, All Teams))).Kiriko_Tele = 1;
		Wait(0.200, Ignore Condition);
	}
}

rule("키리코 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		키리코;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Event Player.KRK_C1 == 1;
	}

	action
	{
		Abort If(Event Player.KRK_CELL2 != 0);
		Event Player.KRK_C1 = 0;
		Event Player.KRK_CELL2 = Event Player.KRK_CELL1;
	}
}

rule("겐지 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		겐지;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Set Ultimate Charge(Event Player, 100);
		Press Button(Event Player, Button(Ultimate));
		Filtered Array(All Living Players(All Teams), Current Array Element != Players On Hero(Hero(겐지), All Teams)).GD += -1;
	}
}

rule("겐지 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		겐지;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Set Status(Event Player, Null, Phased Out, 3);
	}
}

rule("리퍼 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		리퍼;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Set Primary Fire Enabled(Event Player, True);
	}
}

rule("리퍼 좌클 효과")
{
	event
	{
		Player Dealt Damage;
		All;
		리퍼;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Firing Primary(Event Player) == True;
	}

	action
	{
		Set Status(Victim, Event Player, Stunned, 0.300);
	}
}

rule("리퍼 우클 특전 효과")
{
	event
	{
		Player Died;
		All;
		All;
	}

	condition
	{
		Players On Hero(Hero(리퍼), All Teams).ttek_right_enable == True;
		Is Alive(Players On Hero(Hero(리퍼), All Teams)) == True;
	}

	action
	{
		Set Ultimate Charge(Players On Hero(Hero(리퍼), All Teams), Ultimate Charge Percent(Players On Hero(Hero(리퍼), All Teams)) + 30);
	}
}

rule("[특전] 메이 좌클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		메이;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Event Player.MD += 150;
	}
}

rule("[특전] 메이 우클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		메이;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
	}

	action
	{
		Set Secondary Fire Enabled(Event Player, True);
	}
}

rule("[특전] 메이 우클릭 - 얼리기")
{
	event
	{
		Player Dealt Damage;
		All;
		메이;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Firing Primary(Event Player) != True;
		Is Using Ultimate(Event Player) != True;
	}

	action
	{
		Set Status(Victim, Event Player, Frozen, 0.300);
	}
}

rule("바스티온 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		바스티온;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Set Move Speed(Event Player, 184.615);
		Wait Until(Is Using Ability 1(Event Player) == False, 99999);
		Set Move Speed(Event Player, 120);
	}
}

rule("바스티온 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		바스티온;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Using Ability 1(Event Player) == True;
		Ability Cooldown(Event Player, Button(Secondary Fire)) != 0;
	}

	action
	{
		Set Ability Cooldown(Event Player, Button(Secondary Fire), 0);
	}
}

rule("벤처 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		벤처;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Wait Until(Is Using Ability 1(Event Player) == False, 99999);
		Event Player.M = Players Within Radius(Event Player, 10, Opposite Team Of(Team Of(Event Player)), Surfaces);
		Event Player.M = Filtered Array(Event Player.M, Current Array Element != Event Player);
		Damage(Filtered Array(Event Player.M, Current Array Element != Event Player), Event Player, 100);
		Set Status(Event Player.M, Event Player, Stunned, 1.400);
		Small Message(Event Player.M, Custom String("으윽.. 냄새..."));
	}
}

rule("벤처 우클 특전 효과 - **Chase Player Variable로 수정 by Dote6**")
{
	event
	{
		Ongoing - Each Player;
		All;
		벤처;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Button Held(Event Player, Button(Ability 2)) == True;
		Event Player.WRF == 0;
		Has Status(Event Player, Hacked) == False;
		Has Status(Event Player, Knocked Down) == False;
		Has Status(Event Player, Asleep) == False;
		Has Status(Event Player, Frozen) == False;
		Has Status(Event Player, Rooted) == False;
		Has Status(Event Player, Stunned) == False;
		Is Alive(Event Player) == True;
	}

	action
	{
		투사체 생성(구형 투사체, Event Player, Eye Position(Event Player) + Vector(0, 0.500, 0), Direction From Angles(
			Horizontal Angle From Direction(Facing Direction Of(Event Player)), Vertical Angle From Direction(Facing Direction Of(
			Event Player))), To World, Damage, All Teams, 120, 12, 2.500, Bad Explosion, Explosion Sound, 0.200, 37.500, 100, 20, 2, 100);
		Event Player.WRF = 30;
		Chase Player Variable Over Time(Event Player, WRF, 0, 30, None);
	}
}

rule("벤처 우클 특전 효과 (게이지 표시) - **추가 by Dote6**")
{
	event
	{
		Ongoing - Each Player;
		All;
		벤처;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
	}

	action
	{
		Create Progress Bar HUD Text(Players On Hero(Hero(벤처), All Teams), 3.333 * Event Player.WRF, Custom String("야매강착 남은 쿨타임 : {0}초",
			Round To Integer(Event Player.WRF, Up)), Left, 33, Color(Orange), Color(흰색), Visible To and Values, Visible Never);
	}
}

rule("벤처 E")
{
	event
	{
		Ongoing - Each Player;
		All;
		벤처;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Event Player.WRF == 0;
	}

	action
	{
		Small Message(Event Player, Custom String("야매강착 사용가능"));
	}
}

rule("소전 좌클 특전 효과")
{
	event
	{
		Player Dealt Damage;
		All;
		소전;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Set Status(Victim, Event Player, Stunned, 0.300);
	}
}

rule("소전 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		소전;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Set Move Speed(Event Player, 200);
		Wait Until(Is Using Ability 1(Event Player) == False, 99999);
		Set Move Speed(Event Player, 120);
	}
}

rule("[특전] 솔저: 76 좌클릭")
{
	event
	{
		Ongoing - Each Player;
		All;
		솔저: 76;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Standing(Event Player) == True;
		Event Player.WRF < 10;
	}

	action
	{
		Set Status(Event Player, Event Player, Phased Out, 9999);
		Wait Until(Is Moving(Event Player), 99999);
		Clear Status(Event Player, Phased Out);
		Event Player.WRF = Event Player.WRF + 1;
	}
}

rule("[특전] 솔저: 76 좌클릭 (게이지 표시)")
{
	event
	{
		Ongoing - Each Player;
		All;
		솔저: 76;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Create Progress Bar HUD Text(Players On Hero(Hero(솔저: 76), All Teams), 10 * Event Player.WRF, Custom String("움직이면 게이 사용횟수 : {0}회",
			Round To Integer(Event Player.WRF, Up)), Left, 33, Color(Orange), Color(흰색), Visible To and Values, Visible Never);
	}
}

rule("솔저: 76 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		솔저: 76;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Set Ability Cooldown(Event Player, Button(Secondary Fire), 0);
		Wait(0.100, Ignore Condition);
		Loop If Condition Is True;
	}
}

rule("솜브라 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		솜브라;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Set Invisible(Event Player, All);
		Wait Until(Is Dead(Event Player), 99999);
		Set Invisible(Event Player, None);
	}
}

rule("솜브라 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		솜브라;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
	}

	action
	{
		Set Secondary Fire Enabled(Event Player, True);
	}
}

rule("[특전] 시메트라 좌클릭 - 버블버블 화상")
{
	event
	{
		Player Dealt Damage;
		All;
		시메트라;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Set Status(Victim, Event Player, Burning, 0.500);
	}
}

rule("[특전] 시메트라 우클릭 - 좌클릭 활성화")
{
	event
	{
		Ongoing - Each Player;
		All;
		시메트라;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Set Primary Fire Enabled(Event Player, True);
	}
}

rule("애쉬 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		애쉬;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Has Status(Event Player, Burning) == True;
	}

	action
	{
		Set Move Speed(Event Player, 120);
	}
}

rule("애쉬 우클 특전 효과")
{
	event
	{
		Player Dealt Damage;
		All;
		애쉬;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Event Was Critical Hit == True;
	}

	action
	{
		Set Status(Victim, Event Player, Stunned, 1.500);
	}
}

rule("에코 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		에코;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Set Melee Enabled(Event Player, True);
	}
}

rule("에코 근공")
{
	event
	{
		Ongoing - Each Player;
		All;
		에코;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Button Held(Event Player, Button(Melee)) == True;
	}

	action
	{
		Wait(Is Meleeing(Event Player) != True, Ignore Condition);
		Set Melee Enabled(Event Player, False);
	}
}

rule("에코 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		에코;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
	}

	action
	{
		Set Ability Cooldown(Event Player, Button(Secondary Fire), 0);
		Press Button(Event Player, Button(Secondary Fire));
	}
}

rule("위도우메이커 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		위도우메이커;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Using Ability 1(Event Player) == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Event Player.SJ_SL = Players Within Radius(Event Player, 2, Opposite Team Of(Team Of(Event Player)), Surfaces);
		Event Player.SJ_SL = Filtered Array(Event Player.SJ_SL, Current Array Element != Event Player);
		Play Effect(All Players(All Teams), Bad Explosion, Color(Red), Event Player, 0.500);
		Play Effect(All Players(All Teams), Ring Explosion, Color(흰색), Event Player, 3);
		Set Status(Event Player.SJ_SL, Event Player, Knocked Down, 2.500);
		Small Message(Event Player.SJ_SL, Custom String("{0} 위도우메이커 : 잠시 지나가실게요!", Hero Icon String(Hero(위도우메이커))));
		Wait(0.050, Ignore Condition);
		Event Player.SJ_SL = Players Within Radius(Event Player, 2, Opposite Team Of(Team Of(Event Player)), Surfaces);
		Event Player.SJ_SL = Filtered Array(Event Player.SJ_SL, Current Array Element != Event Player);
		Set Status(Event Player.SJ_SL, Event Player, Knocked Down, 2.500);
		Small Message(Event Player.SJ_SL, Custom String("{0} 위도우메이커 : 잠시 지나가실게요!", Hero Icon String(Hero(위도우메이커))));
		Wait(0.050, Ignore Condition);
		Loop If Condition Is True;
	}
}

rule("위도우메이커 우클 특전 효과")
{
	event
	{
		Player Dealt Damage;
		All;
		위도우메이커;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Global.RoundNumber >= 12;
	}

	action
	{
		Set Status(Victim, Event Player, Frozen, 2);
	}
}

rule("[위도우메이커] : 우클 특전 - 신화 각성 알림 by 누구인")
{
	event
	{
		Ongoing - Each Player;
		All;
		위도우메이커;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Global.RoundNumber == 12;
	}

	action
	{
		Big Message(All Players(All Teams), Custom String("{0} 위도우메이커 : 좀 싱거웠지? 이제부터 신화 각성이야.", Hero Icon String(Hero(위도우메이커))));
	}
}

rule("정크랫 좌클 특전 효과 (좌클 활성화로 수정, Dote6, 250506)")
{
	event
	{
		Ongoing - Each Player;
		All;
		정크랫;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Set Primary Fire Enabled(Event Player, True);
	}
}

rule("캐서디 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		캐서디;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Set Status(Event Player, Event Player, Phased Out, 9999);
		Wait Until(Is Using Ability 1(Event Player) == False, 99999);
		Clear Status(Event Player, Phased Out);
	}
}

rule("캐서디 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		캐서디;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Match Time > 30;
	}

	action
	{
		Disallow Button(Event Player, Button(Ultimate));
		Set Ultimate Charge(Event Player, 100);
	}
}

rule("토르비욘 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		토르비욘;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Set Ultimate Ability Enabled(Event Player, True);
		Set Ultimate Charge(Event Player, 100);
	}
}

rule("토르비욘 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		토르비욘;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
	}

	action
	{
		Start Scaling Player(Event Player, 1.500, True);
		Set Move Speed(Event Player, 135);
	}
}

rule("트레이서 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		트레이서;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Set Primary Fire Enabled(Event Player, True);
	}
}

rule("트레이서 좌클 넉백")
{
	event
	{
		Player Dealt Damage;
		All;
		트레이서;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Firing Primary(Event Player) == True;
	}

	action
	{
		Abort If Condition Is False;
		Apply Impulse(Victim, Position Of(Victim) - Position Of(Event Player), 6, To World, Cancel Contrary Motion);
	}
}

rule("트레이서 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		트레이서;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Set Player Health(Event Player, 181);
	}
}

rule("파라 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		파라;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Set Primary Fire Enabled(Event Player, True);
	}
}

rule("파라 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		파라;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Set Ability 1 Enabled(Event Player, True);
	}
}

rule("한조 좌클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		한조;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
		Has Spawned(Event Player) == True;
	}

	action
	{
		Create Effect(Filtered Array(All Players(All Teams), Current Array Element != Event Player), Bad Aura, Color(회색), Event Player, 1,
			Visible To Position and Radius);
		Event Player.Y = Last Created Entity;
	}
}

rule("[한조] : 좌클 패시브 - 투명 1 by 누구인")
{
	event
	{
		Ongoing - Each Player;
		All;
		한조;
	}

	condition
	{
		Is Moving(Event Player) == False;
		Has Status(Event Player, Hacked) == False;
		Has Status(Event Player, Burning) == False;
		Has Status(Event Player, Knocked Down) == False;
		Has Status(Event Player, Asleep) == False;
		Has Status(Event Player, Frozen) == False;
		Has Status(Event Player, Rooted) == False;
		Has Status(Event Player, Stunned) == False;
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Set Invisible(Event Player, All);
	}
}

rule("[한조] : 좌클 패시브 - 투명 2")
{
	event
	{
		Ongoing - Each Player;
		All;
		한조;
	}

	condition
	{
		Is Alive(Event Player) == True;
		Is Moving(Event Player) == True;
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Set Invisible(Event Player, None);
	}
}

rule("[한조] : 좌클 패시브 - 투명 3 by 누구인")
{
	event
	{
		Ongoing - Each Player;
		All;
		한조;
	}

	condition
	{
		Is Alive(Event Player) == True;
		(Has Status(Event Player, Hacked) || Has Status(Event Player, Burning) || Has Status(Event Player, Knocked Down) || Has Status(
			Event Player, Asleep) || Has Status(Event Player, Frozen) || Has Status(Event Player, Rooted) || Has Status(Event Player,
			Stunned)) == True;
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Set Invisible(Event Player, None);
	}
}

rule("한조 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		한조;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Alive(Event Player) == True;
	}

	action
	{
		Set Ultimate Charge(Event Player, 100);
		Press Button(Event Player, Button(Ultimate));
	}
}

rule("프레야 좌클 특전 효과")
{
	event
	{
		Player Dealt Damage;
		All;
		프레야;
	}

	condition
	{
		Event Player.ttek_left_enable == True;
	}

	action
	{
		Set Status(Filtered Array(Victim, Victim != Event Player), Event Player, Stunned, 0.600);
	}
}

rule("프레야 우클 특전 효과")
{
	event
	{
		Ongoing - Each Player;
		All;
		프레야;
	}

	condition
	{
		Event Player.ttek_right_enable == True;
		Is Alive(Event Player) == True;
		Has Spawned(Event Player) == True;
		Is Button Held(Event Player, Button(Secondary Fire)) == True;
	}

	action
	{
		Set Move Speed(Event Player, 600);
		Wait Until(Is Firing Primary(Event Player) == True || Is Button Held(Event Player, Button(Secondary Fire)) == False, 100000000);
		Set Move Speed(Event Player, 120);
		Wait(0.250, Ignore Condition);
	}
}

rule("[프레야]: SHIFT 근처에 오면 빙결")
{
	event
	{
		Ongoing - Each Player;
		All;
		프레야;
	}

	condition
	{
		Has Spawned(Event Player) == True;
		Is Alive(Event Player) == True;
		Is Using Ability 1(Event Player) == True;
	}

	action
	{
		Event Player.SJ_SL = Players Within Radius(Event Player, 3.500, Opposite Team Of(Team Of(Event Player)), Surfaces);
		Event Player.SJ_SL = Filtered Array(Event Player.SJ_SL, Current Array Element != Event Player);
		Damage(Event Player.SJ_SL, Event Player, 1);
		Set Status(Event Player.SJ_SL, Event Player, Frozen, 2);
		Wait(0.050, Ignore Condition);
		Event Player.SJ_SL = Players Within Radius(Event Player, 3.500, Opposite Team Of(Team Of(Event Player)), Surfaces);
		Event Player.SJ_SL = Filtered Array(Event Player.SJ_SL, Current Array Element != Event Player);
		Damage(Event Player.SJ_SL, Event Player, 1);
		Set Status(Event Player.SJ_SL, Event Player, Frozen, 2);
		Wait(0.050, Ignore Condition);
		Loop If Condition Is True;
	}
}

rule("프레야 좌클 탄창 0")
{
	event
	{
		Ongoing - Each Player;
		All;
		프레야;
	}

	condition
	{
		Has Spawned(Event Player) == True;
	}

	action
	{
		Set Ammo(Event Player, 0, 0);
		Set Max Ammo(Event Player, 0, 0);
	}
}

rule("[프레야]: 궁극기 쓰면 궁게이지 0아니게")
{
	event
	{
		Ongoing - Each Player;
		All;
		프레야;
	}

	condition
	{
		Is Alive(Event Player) == True;
		Has Spawned(Event Player) == True;
		Is Using Ultimate(Event Player) == True;
	}

	action
	{
		Wait(2, Ignore Condition);
		Set Ultimate Charge(Players On Hero(Hero(프레야), All Teams), 1);
	}
}

rule("[최적화, 코드 단축] 워크샵 맵 제외 모든 맵 통합 - 1 (기존 맵 코드 삭제 후 추가 by Dote6)")
{
	event
	{
		Ongoing - Global;
	}

	action
	{
		Abort If(Current Map == Map(워크샵 개활지));
		Abort If(Current Map == Map(워크샵 개활지 밤));
		Abort If(Current Map == Map(워크샵 그린 스크린));
		Abort If(Current Map == Map(워크샵 방));
		Abort If(Current Map == Map(워크샵 섬));
		Abort If(Current Map == Map(워크샵 섬 밤));
		"대기시간"
		Wait(3, Ignore Condition);
		Global.SphereLocations = Empty Array;
		Global.DynamicTrigger = 1;
		"아누비스 신전"
		Skip If(Current Map != Map(아누비스 신전), 5);
		Global.ArenaID = Random Integer(0, 3);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(-10.023, 3.991, 78.574), Vector(-6.294, 1.640, 58.352), Vector(-22.492, 1.355, 49.061),
			Vector(-24.563, 1.510, 63.824), Vector(-38.163, 1.500, 70.128), Vector(-33.958, 5.703, 63.071)), Array(Vector(8.242, 4.715,
			107.028), Vector(-6.698, 4.332, 122.572), Vector(-22.741, 4.959, 115.978), Vector(-8.088, 0.102, 101.331), Vector(-7.572,
			4.966, 110.400), Vector(-16.049, 4.952, 96.758)), Array(Vector(12.335, 4.409, 13.517), Vector(-4.142, 4.472, 4.543), Vector(
			-3.101, -2.493, 2.490), Vector(10.591, -1.460, -6.867), Vector(18.044, 0.550, 4.262), Vector(-12.136, 0.408, 0.151)), Array(
			Vector(-51.138, 9.509, 32.789), Vector(-21.124, 4.509, 35.133), Vector(-38.660, 5.009, 9.181), Vector(-23.686, 0.511, 15.220),
			Vector(-27.685, 1.335, 43.564), Vector(-45.150, 1.513, 34.443)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-21.233, 5, 62.974), Vector(-7.941, 3.917, 106.735), Vector(3.437, 1.452, 9.337), Vector(-36.195,
			5, 25.499))[Global.ArenaID];
		Global.ArenaRadius = Array(25, 25, 24, 25)[Global.ArenaID];
		"검은 숲 & 검은 숲 겨울"
		Skip If(Current Map != Map(검은 숲) && Current Map != Map(검은 숲 겨울), 5);
		Global.ArenaID = Random Integer(0, 1);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(-5.007, 13.330, 5.695), Vector(-5.268, 18.302, -17.496), Vector(5.029, 12.237,
			-15.982), Vector(-13.313, 13.312, -19.354), Vector(-15.553, 13.314, -0.235), Vector(1.228, 17.749, 5.066)), Array(Vector(
			21.868, 17.296, 35.952), Vector(15.821, 17.300, 7.258), Vector(34.563, 16.225, 17.913), Vector(30.516, 12.298, 33.203), Vector(
			8.855, 11.043, 33.473), Vector(21.223, 10.642, 11.901)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-5.399, 11, -5.732), Vector(20.256, 11.722, 20.300))[Global.ArenaID];
		Global.ArenaRadius = Array(22, 22)[Global.ArenaID];
		"블리자드 월드 겨울"
		Skip If(Current Map != Map(블리자드 월드 겨울), 5);
		Global.ArenaID = Random Integer(0, 5);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(-43.878, -2.213, 144.615), Vector(-65.569, 1.750, 157.914), Vector(-75.877, 0.747,
			137.405), Vector(-78.452, 0.598, 127.631), Vector(-64.400, 0.598, 120.474), Vector(-45.471, -0.205, 133.169)), Array(Vector(
			-62.541, 6.871, 80.174), Vector(-36.664, 5.937, 93.153), Vector(-66.922, 6.734, 103.341), Vector(-54.726, -0.096, 110.193),
			Vector(-41.602, 0.093, 80.160), Vector(-54.173, 0.111, 90.644)), Array(Vector(13.729, -5.100, 13.676), Vector(21.702, -4,
			36.309), Vector(25.018, 0.042, 41.411), Vector(11.974, 0.007, 45.058), Vector(7.833, 0.007, 34.735), Vector(14.968, -4,
			28.823)), Array(Vector(2.912, -4.848, 16.090), Vector(-15.723, -3.848, 0.671), Vector(21.248, -3.797, 2.563), Vector(3.075,
			0.098, 20.472), Vector(2.851, -1.548, -7.139), Vector(3.006, -5.100, 4.097)), Array(Vector(-109.370, 5.048, 131.438), Vector(
			-114.879, 2.045, 157.173), Vector(-134.057, 1.049, 151.706), Vector(-126.781, -2.100, 127.075), Vector(-102.489, -0.955,
			153.859), Vector(-98.641, 5.049, 149.609)), Array(Vector(2.976, 2.299, 66.468), Vector(2.806, 0.212, 47.764), Vector(20.306,
			1.302, 52.497), Vector(-7.539, 6.367, 53.091), Vector(20.483, 2.298, 68.054), Vector(-11.713, 2.252, 74.401)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-63.202, 1.997, 138.997), Vector(-53.431, 0, 92.927), Vector(27.659, -4, 30.937), Vector(2.980,
			-4.620, 4.050), Vector(-112.742, 0.045, 145.669), Vector(2.991, 3.400, 60.364))[Global.ArenaID];
		Global.ArenaRadius = Array(25, 22, 26, 22, 28, 25)[Global.ArenaID];
		"카스티요"
		Skip If(Current Map != Map(카스티요), 5);
		Global.ArenaID = Random Integer(0, 1);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(-116.519, 34.816, 75.082), Vector(-110.561, 33.560, 59.979), Vector(-121.415, 34.816,
			48.202), Vector(-115.875, 38.826, 60.889), Vector(-124.626, 38.804, 74.820), Vector(-129.067, 38.804, 51.166)), Array(Vector(
			-85.643, 38.641, 55.148), Vector(-84.587, 32.556, 40.154), Vector(-107.071, 32.556, 29.777), Vector(-109.785, 32.675, 43.613),
			Vector(-96.813, 33.556, 48.106), Vector(-104.430, 39.556, 42.901)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-125.693, 34.627, 62.748), Vector(-92.803, 32.637, 39.985))[Global.ArenaID];
		Global.ArenaRadius = Array(22, 22)[Global.ArenaID];
		"샤토 기아르 & 샤토 기아르 할로윈"
		Skip If(Current Map != Map(샤토 기야르) && Current Map != Map(샤토 기야르 할로윈), 5);
		Global.ArenaID = Random Integer(0, 2);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(169.102, 5.299, 80.927), Vector(182.399, 1.301, 83.112), Vector(185.355, 6.299,
			76.548), Vector(194.046, 8.298, 93.120), Vector(180.019, 9.301, 102.714), Vector(193.122, 1.301, 80.973)), Array(Vector(
			218.856, 9.251, 62.009), Vector(206.251, 8.342, 68.423), Vector(190.447, 3.251, 57.129), Vector(196.402, 16.748, 64.928),
			Vector(220.217, 14.252, 61.979), Vector(218.723, 12.342, 45.523)), Array(Vector(205.941, 8.327, 105.887), Vector(219.346,
			6.298, 104.617), Vector(224.614, 1.299, 78.474), Vector(206.521, 0.337, 81.374), Vector(232.690, 2.299, 90.794), Vector(
			226.233, 4.965, 111.784)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(177.896, 5.299, 89.855), Vector(206.289, 9.249, 51.313), Vector(215.755, 2.302, 93.491))
			[Global.ArenaID];
		Global.ArenaRadius = Array(22, 22, 27)[Global.ArenaID];
		"도라도"
		Skip If(Current Map != Map(도라도), 5);
		Global.ArenaID = Random Integer(0, 5);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(3.780, 0.210, -14.160), Vector(15.480, 1.610, -2.380), Vector(22.390, 4.290, -10.560),
			Vector(8.310, 11.650, -3.540), Vector(21.260, 10.130, -5.820), Vector(15.810, 4.560, -25.560)), Array(Vector(61.600, 9.380,
			7.290), Vector(50.670, 4.600, 20.560), Vector(39.930, 2.660, 12.570), Vector(34.150, 3.400, -0.520), Vector(34.770, 9.600,
			4.250), Vector(38.790, 9.600, -8.250)), Array(Vector(55.813, 7.314, -2.194), Vector(70.549, 7.302, -1.754), Vector(80.790,
			7.283, -16.928), Vector(55.098, 7.299, -30.846), Vector(48.519, 7.005, -18.486), Vector(59.948, 7.080, -24.319)), Array(Vector(
			101.930, 11.640, 10.340), Vector(88.790, 13.350, 24.180), Vector(78.990, 8.600, 9.750), Vector(97.590, 17.640, -3.650), Vector(
			96.240, 18.610, 11.910), Vector(95.180, 7.600, -2.230)), Array(Vector(136.720, 18.350, 12.940), Vector(151.180, 10.610,
			-6.720), Vector(134.490, 10.610, 9.190), Vector(137.450, 10.600, -1.340), Vector(156.840, 10.610, 3.900), Vector(152.660,
			14.640, 16.910)), Array(Vector(184.473, 14.398, 34.338), Vector(194.953, 15.310, 24.146), Vector(203.479, 16.292, 31.939),
			Vector(206.724, 15.302, 46.944), Vector(194.280, 12.310, 62.507), Vector(178.562, 12.759, 53.825)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(12.830, 1, -11.290), Vector(48.480, 7, 4.400), Vector(64.020, 4.550, -17.670), Vector(89.720, 11,
			7.440), Vector(150.490, 8.010, 8.630), Vector(192.014, 15.580, 42.772))[Global.ArenaID];
		Global.ArenaRadius = Array(20, 19, 22, 20, 20, 25)[Global.ArenaID];
		"탐사 기지: 남극 & 탐사 기지: 남극 겨울"
		Skip If(Current Map != Map(탐사 기지: 남극) && Current Map != Map(탐사 기지: 남극 겨울), 5);
		Global.ArenaID = Random Integer(0, 2);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(17.952, 10.243, 28.279), Vector(7.877, 7.295, 40.161), Vector(-8.754, 7.591, 36.047),
			Vector(-11.914, 6.593, 14.570), Vector(2.439, 12.252, 11.905), Vector(2.131, 11.885, 25.123)), Array(Vector(17.959, 12.301,
			14.172), Vector(17.978, 12.302, -14.024), Vector(20.813, 6.315, -17.151), Vector(20.988, 6.309, 17.225), Vector(29.206, 3.298,
			-0.002), Vector(9.345, 4.491, 0.142)), Array(Vector(-9.776, 8.823, -0.424), Vector(-32.321, 9.299, -0.030), Vector(-5.953,
			12.302, -11.973), Vector(-6.154, 12.302, 12.029), Vector(-19.218, 12.302, -6.420), Vector(-19.095, 12.302, 6.916)))
			[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(2.143, 7.651, 25.050), Vector(18.196, 0.301, 0.019), Vector(-15.253, 0.566, -0.192))
			[Global.ArenaID];
		Global.ArenaRadius = Array(22, 23, 22)[Global.ArenaID];
		"아이헨발데 할로윈"
		Skip If(Current Map != Map(아이헨발데 할로윈), 5);
		Global.ArenaID = Random Integer(0, 5);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(99.544, 12.743, -65.279), Vector(107.877, 12.727, -55.774), Vector(97.014, 10.727,
			-33.316), Vector(80.632, 15.723, -38.210), Vector(77.997, 12.723, -58.666), Vector(104.131, 10.723, -39.892)), Array(Vector(
			65.047, 11.937, -95.908), Vector(66.480, 8.216, -108.012), Vector(73.253, 10.730, -114.973), Vector(87.496, 11.425, -113.752),
			Vector(95.708, 12.725, -102.279), Vector(82.710, 12.688, -87.419)), Array(Vector(4, 0.696, -8.188), Vector(-18.545, 0.301,
			-10.438), Vector(-30.137, -0.958, -20.156), Vector(-21.269, 2.269, -36.067), Vector(6.697, 4.111, -27.286), Vector(-1.796,
			2.302, -37.589)), Array(Vector(12.867, 6.251, -57.581), Vector(2.175, 6.249, -47.010), Vector(14.031, 4.901, -48.458), Vector(
			22.722, 5.065, -60.107), Vector(-2.050, 6.749, -70.329), Vector(12.884, 6.069, -72.743)), Array(Vector(55.973, 21.305,
			-67.446), Vector(66.093, 5.197, -83.278), Vector(54.370, 18.343, -81.293), Vector(59.040, 12.004, -59.384), Vector(54.893,
			7.021, -67.835), Vector(55.649, 12.056, -80.844)), Array(Vector(126.500, 16.065, -15.341), Vector(113.913, 11.021, -22.750),
			Vector(130.131, 9.021, -38.075), Vector(111.324, 9.954, -38.853), Vector(126.144, 11.021, -15.549), Vector(141.001, 11.655,
			-30.224)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(93.079, 10, -49.819), Vector(79.213, 12, -100.163), Vector(-10.269, 1.555, -20.869), Vector(
			9.500, 3.980, -60.610), Vector(65.398, 13.021, -73.105), Vector(123.546, 8.024, -25.876))[Global.ArenaID];
		Global.ArenaRadius = Array(22, 20, 25, 18, 18, 22)[Global.ArenaID];
		"하나무라"
		Skip If(Current Map != Map(하나무라), 5);
		Global.ArenaID = Random Integer(0, 3);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(7.561, -1.106, -66.092), Vector(27.793, 2.287, -59.635), Vector(12.993, 0.252,
			-28.993), Vector(-3.307, -1.749, -42.591), Vector(-0.106, -1.610, -33.113), Vector(29.182, -1.046, -38.521)), Array(Vector(
			20.058, 1.999, 20.765), Vector(7.022, -0.002, 7.966), Vector(0.490, 3.999, 15.096), Vector(-11.472, 0.998, 29.048), Vector(
			8.406, -1.106, 33.018), Vector(8.985, 3.998, 17.919)), Array(Vector(-12.608, -4.802, -70.479), Vector(-0.551, -4.802, -74.055),
			Vector(9.750, -4.799, -88.853), Vector(-0.551, -0.701, -96.963), Vector(-16.505, -0.452, -90.303), Vector(4.130, -0.702,
			-70.125)), Array(Vector(51.915, -1.467, 10.011), Vector(41.934, 0.998, 1.334), Vector(31.914, 0.247, 12.392), Vector(40.850,
			0.306, 34.546), Vector(31.156, 2.998, 27.521), Vector(48.105, 6.086, 3.836)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(12.889, -0.025, -48.918), Vector(2.029, 4.265, 21.273), Vector(-3.077, -3.842, -82.494), Vector(
			40.891, 0, 17.986))[Global.ArenaID];
		Global.ArenaRadius = Array(25, 24, 20, 21)[Global.ArenaID];
		"하바나"
		Skip If(Current Map != Map(하바나), 5);
		Global.ArenaID = Random Integer(0, 3);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(120.428, 6.424, -46.777), Vector(124.455, 6.251, -61.850), Vector(135.747, 12.253,
			-63.396), Vector(127.746, 6.252, -29.864), Vector(147.010, 9.278, -30.016), Vector(123.784, 11.252, -31.422)), Array(Vector(
			27.644, 10.298, -92.618), Vector(19.776, 6.301, -92.438), Vector(8.171, 6.260, -80.598), Vector(16.315, 6.302, -101.070),
			Vector(27.181, 12.302, -74.855), Vector(27.341, 6.299, -81.784)), Array(Vector(-102.339, 4.148, -50.229), Vector(-79.130,
			4.298, -72.768), Vector(-65.507, 5.101, -63.475), Vector(-66.726, 4.250, -39.106), Vector(-86.460, 4.299, -36.470), Vector(
			-85.442, 4.148, -56.481)), Array(Vector(-23.818, 12.299, -39.727), Vector(-15.450, 11.298, -51.434), Vector(-15.539, 6.299,
			-43.348), Vector(-37.132, 6.148, -51.220), Vector(-34.075, 6.141, -34.025), Vector(-24.023, 6.326, -67.319)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(136.308, 6.418, -46.460), Vector(22.280, 3, -89.852), Vector(-81.613, 4.414, -52.022), Vector(
			-23.799, 4, -51.046))[Global.ArenaID];
		Global.ArenaRadius = Array(27, 23, 25, 30)[Global.ArenaID];
		"할리우드"
		Skip If(Current Map != Map(할리우드), 5);
		Global.ArenaID = Random Integer(0, 2);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(-21.825, 5.751, -53.209), Vector(-15.543, 5.660, -41.107), Vector(-13.768, 1.730,
			-64.351), Vector(-3.610, 10.010, -59.643), Vector(1.174, 2, -60.099), Vector(-7.441, 2.500, -43.522)), Array(Vector(8.023,
			12.903, -46.957), Vector(11.605, 7.023, -43.422), Vector(7.457, 1.750, -31.682), Vector(4.864, 10.750, -31.440), Vector(31.646,
			1.750, -33.111), Vector(22.634, 1.605, -48.481)), Array(Vector(49.420, 2.750, -60.909), Vector(41.635, 2.751, -54.100), Vector(
			35.058, 2.750, -52.456), Vector(19.082, 1.605, -63.901), Vector(30.488, 1.858, -76.833), Vector(23.338, 1.615, -86.525)))
			[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-8.701, 2.980, -53.664), Vector(16.847, 3, -38.440), Vector(38.525, 2.855, -70.368))
			[Global.ArenaID];
		Global.ArenaRadius = Array(20, 20, 28)[Global.ArenaID];
		"할리우드 할로윈"
		Skip If(Current Map != Map(할리우드 할로윈), 5);
		Global.ArenaID = Random Integer(0, 2);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(-39.965, 2.001, 3.190), Vector(-44.435, 0.999, -7.825), Vector(-15.511, 1.999,
			-13.294), Vector(-11.610, 1.856, -3.653), Vector(-37.485, 5.999, 9.768), Vector(-21.036, 6.990, -10.814)), Array(Vector(
			-13.489, 0.310, 43.567), Vector(5.289, 0.154, 55.065), Vector(5.452, 0.300, 67.450), Vector(-21.421, 1.302, 69.204), Vector(
			-30.095, 0.304, 65.672), Vector(-22.345, 1.608, 52.130)), Array(Vector(19.560, 4.322, 27.842), Vector(-1.195, 2.048, 13.441),
			Vector(-5.016, 1.598, 45.872), Vector(15.211, 0.302, 41.485), Vector(7.545, 6.304, 45.657), Vector(-9.550, 1.893, 27.401)))
			[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-27.710, 3.460, -3.390), Vector(-11.741, 1.306, 61.536), Vector(7.019, 2.979, 31.905))
			[Global.ArenaID];
		Global.ArenaRadius = Array(23, 25, 29)[Global.ArenaID];
		"호라이즌 달 기지"
		Skip If(Current Map != Map(호라이즌 달 기지), 5);
		Global.ArenaID = Random Integer(0, 3);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(-35.015, 5.248, -140.992), Vector(-49.489, 5.252, -136.517), Vector(-44.976, 10.249,
			-129.563), Vector(-47.141, 5.611, -114.763), Vector(-31.716, 3.248, -112.881), Vector(-23.209, 4.749, -135.666)), Array(Vector(
			84.065, 14, -71.824), Vector(70.813, 7, -55.105), Vector(83.304, 6.775, -61.717), Vector(60.364, 5.991, -69.079), Vector(
			68.489, 8, -83.054), Vector(53.437, 14, -76.054)), Array(Vector(-2.385, 3, -111.115), Vector(-3.746, 9, -106.019), Vector(
			20.456, 7.640, -98.606), Vector(10.672, 7, -82.979), Vector(-1.513, 6, -84.130), Vector(-10.393, 6, -90.653)), Array(Vector(
			96.902, 15, -66.880), Vector(98.537, 20, -57.172), Vector(88.145, 20, -62.929), Vector(86.267, 15, -51.510), Vector(88.396, 10,
			-43.005), Vector(95.719, 10, -46.503)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-36.661, 5.749, -127.331), Vector(65.749, 10, -68.593), Vector(5.120, 7.250, -96.389), Vector(
			94.438, 12.549, -55.434))[Global.ArenaID];
		Global.ArenaRadius = Array(22, 23, 22, 20)[Global.ArenaID];
		"일리오스 등대"
		Skip If(Current Map != Map(일리오스 등대), 5);
		Global.ArenaID = Random Integer(0, 1);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(344.843, -18.641, -21.011), Vector(326.536, -20.641, -14.477), Vector(330.752, -24.739,
			6.858), Vector(340.557, -24.641, 7.992), Vector(350.986, -24.740, 9.011), Vector(345.881, -24.141, -15.618)), Array(Vector(
			328.378, -23.641, -59.227), Vector(318.791, -23.667, -35.215), Vector(344.729, -25.641, -58.878), Vector(342.535, -23.641,
			-25.002), Vector(329.833, -23.667, -39.910), Vector(353.792, -25.641, -36.891)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(341.681, -23.469, -5.086), Vector(335.269, -27, -42.097))[Global.ArenaID];
		Global.ArenaRadius = Array(22, 25)[Global.ArenaID];
		"일리오스 폐허"
		Skip If(Current Map != Map(일리오스 폐허), 5);
		Global.ArenaID = Random Integer(0, 1);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(-40.078, 60.618, -160.513), Vector(-23.391, 58.616, -156.294), Vector(-11.207, 61.218,
			-174.588), Vector(-26.388, 58.615, -183.713), Vector(-38.459, 58.615, -173.898), Vector(-26.822, 59.830, -169.609)), Array(
			Vector(28.640, 61.707, -146.680), Vector(28.644, 57.665, -141.739), Vector(40.176, 61.153, -167.592), Vector(17.113, 61.154,
			-167.436), Vector(41.725, 60.857, -153.755), Vector(16.176, 61.108, -153.629)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-26.859, 55.830, -169.272), Vector(28.454, 57.666, -157.398))[Global.ArenaID];
		Global.ArenaRadius = Array(22, 25)[Global.ArenaID];
		"일리오스 우물"
		Skip If(Current Map != Map(일리오스 우물), 5);
		Global.ArenaID = Random Integer(0, 1);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(-225.675, -1.248, 17.557), Vector(-247.466, -1.252, -4.515), Vector(-247.265, -2.782,
			18.934), Vector(-230.499, 5.346, 12.017), Vector(-243.906, 5.335, -0.077), Vector(-222.113, 1.183, 0.524)), Array(Vector(
			-289.355, -3.293, 33.934), Vector(-268.009, -1.303, 52.343), Vector(-250.755, -2.996, 41.275), Vector(-263.659, -4.922,
			18.968), Vector(-277.164, -4.995, 20.953), Vector(-279.521, -3.302, 50.802)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-236.733, 0.169, 6.328), Vector(-274.710, -2.045, 37.272))[Global.ArenaID];
		Global.ArenaRadius = Array(22, 28)[Global.ArenaID];
		"카네자카"
		Skip If(Current Map != Map(카네자카), 5);
		Global.ArenaID = Random Integer(0, 3);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(3.269, 6, 11.030), Vector(-16.920, 6.003, 14.447), Vector(-26.518, 5.840, 21.754),
			Vector(-21.615, 10.002, 21.279), Vector(-8.052, 10, 34.654), Vector(-10.857, 5.840, 22.153)), Array(Vector(-46.315, 13,
			-23.479), Vector(-37.938, 7.003, -21.840), Vector(-29.793, 6.564, -8.659), Vector(-30.680, 10.892, -9.595), Vector(-27.060, 10,
			3.230), Vector(-51.509, 9, 2.736)), Array(Vector(-27.082, 6.175, -44.941), Vector(-33.828, 9, -54.313), Vector(-63.079, 12,
			-30.740), Vector(-50.749, 13, -27.643), Vector(-42.429, 10, -30.461), Vector(-36.562, 6.500, -29.683)), Array(Vector(-19.731,
			10, -24.768), Vector(-19.735, 6, -28.460), Vector(-8.962, 4.922, -38.295), Vector(-20.015, 7.010, -51.722), Vector(5.202, 8,
			-41.004), Vector(-6.101, 6, -19.756)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-10.857, 9.733, 22.153), Vector(-40.526, 8.250, -6.718), Vector(-47.600, 12.250, -43.090),
			Vector(-11.067, 7.291, -36.269))[Global.ArenaID];
		Global.ArenaRadius = Array(22, 25, 25, 24)[Global.ArenaID];
		Start Rule(Map2, Do Nothing);
	}
}

rule("[최적화, 코드 단축] 워크샵 맵 제외 모든 맵 통합 - 2 (기존 맵 코드 삭제 후 추가 by Dote6)")
{
	event
	{
		Subroutine;
		Map2;
	}

	action
	{
		"왕의 길 겨울"
		Skip If(Current Map != Map(왕의 길 겨울), 5);
		Global.ArenaID = Random Integer(0, 5);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(10.721, 0.114, 11.148), Vector(-18.654, 1.486, 6.695), Vector(-19.952, 0.128, -5.108),
			Vector(-2.684, 0.118, -15.100), Vector(12.537, 1.252, -3.927), Vector(-3.820, 0.319, 16.920)), Array(Vector(-68.939, 0.756,
			-51.265), Vector(-50.289, 0.036, -32.759), Vector(-76.885, 0.292, -21.457), Vector(-78.197, 3.801, -28.986), Vector(-70.996,
			0.749, -36.036), Vector(-82.612, 0.537, -46.428)), Array(Vector(-2.853, 39.487, -90.908), Vector(-31.630, 39.487, -96.002),
			Vector(-38.069, 39.487, -60.188), Vector(-9.556, 39.487, -55.060), Vector(-22.056, 39.486, -65.969), Vector(-18.479, 39.487,
			-86.231)), Array(Vector(-89.695, 6.944, -5.857), Vector(-92.832, 1.107, 8.778), Vector(-55.629, 0.005, 2.791), Vector(-69.855,
			-0.223, -18.511), Vector(-60.958, 3.007, -4.829), Vector(-80.515, 6.008, -13.192)), Array(Vector(-158.921, -2.929, 25.908),
			Vector(-136.626, -1.920, 33.759), Vector(-147.093, -0.878, 36.412), Vector(-129.832, -1.225, 20.267), Vector(-165.940, 0.076,
			23.535), Vector(-151.733, 0.085, 5.611)), Array(Vector(-123.385, 1.071, -14.243), Vector(-131.058, -1.016, -1.642), Vector(
			-136.928, -0.929, 11.388), Vector(-118.826, 1.071, 29.083), Vector(-100.729, 5.080, 8.410), Vector(-101.829, 1.072, 2.832)))
			[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-2.640, -1.140, 1.090), Vector(-68.334, 4.799, -36.101), Vector(-20.767, 40.536, -75.040),
			Vector(-75.354, 1.101, 3.707), Vector(-148.963, -1.642, 24.237), Vector(-122.727, 0.029, 6.605))[Global.ArenaID];
		Global.ArenaRadius = Array(22, 24, 30, 27, 24, 29)[Global.ArenaID];
		"리장 관제 센터 & 리장 관제 센터 설날"
		Skip If(Current Map != Map(리장 관제 센터) && Current Map != Map(리장 관제 센터 설날), 5);
		Global.ArenaID = Random Integer(0, 2);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(14.224, 270.252, 321.235), Vector(-14.224, 270.252, 321.235), Vector(0.129, 270.301,
			307.871), Vector(0.043, 274.252, 335.803), Vector(-0.235, 278.251, 305.519), Vector(0.085, 270.249, 328.220)), Array(Vector(
			14.224, 270.252, 321.235), Vector(11.124, 270.252, 336.043), Vector(27.259, 267.299, 311.862), Vector(41.927, 265.298,
			329.777), Vector(37.191, 270.298, 340.364), Vector(23.113, 270.302, 346.111)), Array(Vector(-12.745, 269, 294.036), Vector(
			-27.858, 267, 294.202), Vector(-40.481, 267, 296.336), Vector(-32.177, 267, 279.962), Vector(-18.394, 267, 272.618), Vector(
			-11.887, 267.167, 278.502)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-0.194, 265.248, 317.667), Vector(25.224, 267.299, 327.347), Vector(-28.482, 268.250, 285.838))
			[Global.ArenaID];
		Global.ArenaRadius = Array(23, 23, 22)[Global.ArenaID];
		"리장 정원 & 리장 정원 설날"
		Skip If(Current Map != Map(리장 정원) && Current Map != Map(리장 정원 설날), 5);
		Global.ArenaID = Random Integer(0, 2);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(-41.244, 98.302, 164.555), Vector(-49.988, 94.299, 163.423), Vector(-51.132, 95.299,
			134.318), Vector(-31.623, 94.302, 146.024), Vector(-41.700, 96.176, 140.694), Vector(-67.251, 94.798, 156.686)), Array(Vector(
			-5.955, 96, 117.981), Vector(-19.317, 96, 132.907), Vector(0.026, 94, 154.316), Vector(12.416, 94.148, 149.919), Vector(8.679,
			95.974, 126.335), Vector(2.366, 94, 144.313)), Array(Vector(32.092, 98, 164.936), Vector(25.255, 94.974, 158.074), Vector(
			18.937, 97.900, 182.086), Vector(12.825, 94, 172.352), Vector(0.217, 94, 180.462), Vector(4.950, 94.148, 162.144)))
			[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-48.944, 96.196, 154.131), Vector(-0.022, 85, 135.899), Vector(17.955, 90, 175.271))
			[Global.ArenaID];
		Global.ArenaRadius = Array(25, 25, 24)[Global.ArenaID];
		"리장 야시장 & 리장 야시장 설날"
		Skip If(Current Map != Map(리장 야시장) && Current Map != Map(리장 야시장 설날), 5);
		Global.ArenaID = Random Integer(0, 2);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(-42.727, -1.249, -17.396), Vector(-56.987, 2.252, -13.605), Vector(-71.871, 5.749,
			-12.547), Vector(-48.151, 6.249, -4.297), Vector(-47.153, 2.249, -29.273), Vector(-71.858, 3.751, -29.721)), Array(Vector(
			9.728, 0, -17.726), Vector(27.516, 0, -12.719), Vector(27.434, 0, -32.703), Vector(10.588, -1, -34.516), Vector(26.362, 6,
			-27.873), Vector(17.973, 6, -13.419)), Array(Vector(-12.230, -3, -57.419), Vector(14.130, -3, -57.419), Vector(-7.487, -1,
			-48.443), Vector(9.387, -1, -48.443), Vector(0.931, -1, -71.179), Vector(1.187, -2, -81.450)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-59.547, 3.252, -17.488), Vector(17.747, 1.162, -23.430), Vector(1.202, -5, -63.953))
			[Global.ArenaID];
		Global.ArenaRadius = Array(22, 20, 22)[Global.ArenaID];
		"말레벤토"
		Skip If(Current Map != Map(말레벤토), 5);
		Global.ArenaID = Random Integer(0, 3);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(4.248, 1.556, 30.277), Vector(5.046, 6.006, 23.872), Vector(11.205, 4, 33.836), Vector(
			0.072, 9.035, 41.417), Vector(0.030, 2.673, 45.635), Vector(-0.014, 12, 25.840)), Array(Vector(-19.197, -3, -12.854), Vector(
			-20.471, 2, -12.526), Vector(-0.619, -2, -22.804), Vector(0.214, 5.001, -25.002), Vector(-10.741, 0, -3.362), Vector(6.522, -1,
			-16.439)), Array(Vector(-17.673, 5, 15.254), Vector(-10.778, 1.002, 22.009), Vector(-10.400, 1.998, 28.276), Vector(-18.145,
			2.018, 42.797), Vector(-34.797, 4.750, 22.514), Vector(-27.356, -0.019, 27.977)), Array(Vector(11.178, 3, -12.392), Vector(
			23.186, 1, -0.729), Vector(33.048, 5.365, 4.765), Vector(23.655, 3, 19.842), Vector(0.027, 7.500, 3.311), Vector(4.021, 3.002,
			13.184)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(0.014, 2.840, 34), Vector(-7.671, 0.250, -16.944), Vector(-20.855, 2.386, 28.342), Vector(17.125,
			7.714, 4.096))[Global.ArenaID];
		Global.ArenaRadius = Array(15, 19, 20, 22)[Global.ArenaID];
		"네크로폴리스"
		Skip If(Current Map != Map(네크로폴리스), 5);
		Global.ArenaID = Random Integer(0, 1);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(8.884, 1.304, 0.372), Vector(-0.193, 1.304, 10.548), Vector(-0.218, 1.309, -12.088),
			Vector(-20.236, 3.301, 0.074), Vector(-6.598, -5.702, 0.305), Vector(-16.234, -3.702, 0.002)), Array(Vector(3.518, 10.021,
			26.276), Vector(10.454, 9.331, 20), Vector(27.509, 5.012, 25.438), Vector(20.759, 1, 8.066), Vector(8.446, 1.005, 12.945),
			Vector(5.860, 3, 21.751)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-8.257, 1.256, 0.055), Vector(20.424, 7.891, 24.746))[Global.ArenaID];
		Global.ArenaRadius = Array(22, 21)[Global.ArenaID];
		"네팔 성소"
		Skip If(Current Map != Map(네팔 성소), 5);
		Global.ArenaID = Random Integer(0, 3);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(89.590, 130.100, -77.760), Vector(96.860, 132.100, -63.990), Vector(93.620, 135.600,
			-87.630), Vector(80.980, 129.900, -64.230), Vector(76.990, 131.480, -87.380), Vector(104.040, 132.100, -54)), Array(Vector(
			81.949, 131.903, -23.994), Vector(89.871, 128.249, -9.852), Vector(98.498, 128.248, -0.066), Vector(96.925, 132.986, -3.127),
			Vector(111.052, 132.249, -22.058), Vector(104.598, 132.249, -27.160)), Array(Vector(79.800, 128.280, 0.030), Vector(69.750,
			130.100, 9.140), Vector(69.750, 130.100, -8.940), Vector(64.430, 132.100, 0.070), Vector(52.950, 130.130, 5.970), Vector(
			52.920, 130.130, -6.170)), Array(Vector(65.268, 129.850, 25.805), Vector(56.877, 128, 29.974), Vector(66.097, 127.800, 44.833),
			Vector(74.857, 130, 53.974), Vector(87.430, 130.216, 43.575), Vector(85.657, 131.850, 26.814)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(99.340, 132, -79.150), Vector(94.574, 130.098, -16.599), Vector(68.630, 132, 0), Vector(72.596,
			132, 37.965))[Global.ArenaID];
		Global.ArenaRadius = Array(30, 22, 20, 22)[Global.ArenaID];
		"네팔 제단"
		Skip If(Current Map != Map(네팔 제단), 5);
		Global.ArenaID = Random Integer(0, 1);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(-80.206, 8.251, 0.107), Vector(-72.845, 10.248, -15.190), Vector(-55.607, 13.098,
			0.189), Vector(-57.210, 10.258, 12.911), Vector(-73.518, 10.254, 14.706), Vector(-56.793, 10.776, -11.727)), Array(Vector(
			-28.652, 15.361, 64.886), Vector(-33.157, 16.828, 99.102), Vector(-20.080, 19.786, 91.954), Vector(-14.958, 22.301, 77.799),
			Vector(-50.365, 15.301, 78.298), Vector(-19.961, 22.299, 59.963)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-66.456, 14, -0.102), Vector(-28.869, 16.299, 80.758))[Global.ArenaID];
		Global.ArenaRadius = Array(22, 30)[Global.ArenaID];
		"네팔 마을"
		Skip If(Current Map != Map(네팔 마을), 5);
		Global.ArenaID = Random Integer(0, 1);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(-156.789, -88.882, -10.148), Vector(-157.134, -88.853, 9.580), Vector(-175.122,
			-91.617, 13.941), Vector(-175.944, -91.639, -14.416), Vector(-189.456, -86.748, -0.119), Vector(-189.477, -93.452, -0.129)),
			Array(Vector(-161.153, -89.728, 41.955), Vector(-181.099, -89.698, 23.843), Vector(-177.330, -89.699, 41.860), Vector(-182.545,
			-95.583, 45.717), Vector(-186.657, -93.461, 35.369), Vector(-166.422, -97.625, 49.688)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-173.379, -86.825, -0.438), Vector(-177.351, -96.698, 40.678))[Global.ArenaID];
		Global.ArenaRadius = Array(22, 22)[Global.ArenaID];
		"오아시스 도심"
		Skip If(Current Map != Map(오아시스 도심), 5);
		Global.ArenaID = Random Integer(0, 1);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(123.084, 4.253, 245.295), Vector(136.490, 2.253, 240.475), Vector(141.576, 4.252,
			226.719), Vector(118.014, 1.249, 222.183), Vector(139.587, 3.166, 219.783), Vector(115.653, 3.397, 244.037)), Array(Vector(
			141.753, 4.299, 267.606), Vector(163.461, 4.299, 245.835), Vector(149.764, 2.302, 253.915), Vector(168.243, 4.301, 272.276),
			Vector(147.615, 11.821, 269.487), Vector(165.539, 11.821, 251.618)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(124.608, 0.689, 228.560), Vector(157.528, 5.299, 261.737))[Global.ArenaID];
		Global.ArenaRadius = Array(22, 22)[Global.ArenaID];
		"오아시스 정원"
		Skip If(Current Map != Map(오아시스 정원), 5);
		Global.ArenaID = Random Integer(0, 1);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(156.246, 7.799, -219.425), Vector(168.649, 7.798, -219.998), Vector(176.385, 5.798,
			-242.330), Vector(170.848, 6.408, -250.451), Vector(151.838, 7.835, -253.840), Vector(143.833, 7.836, -234.449)), Array(Vector(
			126.399, 7.789, -243.699), Vector(108.142, 7.751, -240.944), Vector(105.319, 4.749, -223.152), Vector(137.316, 7.789,
			-232.670), Vector(134.662, 7.749, -215.147), Vector(117.269, 4.752, -211.663)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(161.976, 10.249, -238.688), Vector(120.993, 4.748, -227.352))[Global.ArenaID];
		Global.ArenaRadius = Array(25, 25)[Global.ArenaID];
		"오아시스 대학"
		Skip If(Current Map != Map(오아시스 대학), 5);
		Global.ArenaID = Random Integer(0, 1);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(-170.518, 15.299, 35.813), Vector(-207.366, 17.299, 54.096), Vector(-201.936, 15.299,
			33.774), Vector(-193.234, 9.298, 25.754), Vector(-174.047, 16.298, 58.854), Vector(-188.016, 19.240, 67.640)), Array(Vector(
			-182.432, 15.299, 0.067), Vector(-188.021, 16.298, 11.814), Vector(-187.968, 16.302, -12.526), Vector(-183.125, 9.298, -0.101),
			Vector(-209.603, 13.301, 8.107), Vector(-210.125, 13.302, -7.429)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-187.521, 16.958, 44.979), Vector(-194.958, 16.302, -0.088))[Global.ArenaID];
		Global.ArenaRadius = Array(26, 25)[Global.ArenaID];
		"파리"
		Skip If(Current Map != Map(파리), 5);
		Global.ArenaID = Random Integer(0, 3);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(-61.244, 14.997, -19.977), Vector(-53.870, 10.648, -6.856), Vector(-53.177, 12.288,
			-28.394), Vector(-36.264, 14.288, -9.306), Vector(-34.747, 10.222, -23.730), Vector(-60.299, 14.289, 0.070)), Array(Vector(
			-80.588, 12.299, -76.458), Vector(-87.644, 13.298, -104.520), Vector(-76.523, 13.046, -68.951), Vector(-59.789, 15.299,
			-93.918), Vector(-92.799, 12.401, -91.988), Vector(-59.849, 11.337, -72.177)), Array(Vector(-103.950, 11.390, -38.690), Vector(
			-128.040, 10.600, -67.220), Vector(-118.060, 13.600, -82.590), Vector(-104.250, 12.600, -75.290), Vector(-100.530, 12.600,
			-53.770), Vector(-113.360, 10.600, -52.920)), Array(Vector(-21.079, 10.324, -56.245), Vector(-6.135, 15.298, -67.561), Vector(
			11.041, 10.222, -61.219), Vector(-7.153, 10.302, -68.260), Vector(-14.661, 16.302, -58.435), Vector(3.775, 10.815, -40.142)))
			[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-50, 9.333, -14.371), Vector(-70.810, 9.299, -90.860), Vector(-116.430, 9.990, -59.980), Vector(
			-4.789, 11.222, -54.760))[Global.ArenaID];
		Global.ArenaRadius = Array(22, 27, 30, 22)[Global.ArenaID];
		"페트라"
		Skip If(Current Map != Map(페트라), 5);
		Global.ArenaID = Random Integer(0, 3);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(-27.952, -5, 13.657), Vector(-18.999, -11.499, 8.962), Vector(-20.358, -3.250, -2.028),
			Vector(-18.027, 0, 2.959), Vector(-30.273, -9.427, -9.939), Vector(-38.536, -12.534, 7.898)), Array(Vector(-17.432, -8.062,
			28.879), Vector(-2, 0, 39), Vector(-11.584, -6.763, 44.561), Vector(-1.988, -11, 27.713), Vector(-5.354, -1, 33.921), Vector(
			-3.551, -12.876, 43.411)), Array(Vector(2.009, -6, -5.682), Vector(20.560, -6, 9.015), Vector(1.988, -9.978, 8.998), Vector(
			2.010, 0.020, 15.343), Vector(1.930, -11, 23.899), Vector(-16.925, -10.463, 8.910)), Array(Vector(23.607, -9.209, 29.376),
			Vector(23.607, -1.209, 29.376), Vector(23.607, 6.791, 29.376), Vector(18.979, 6.791, 35.137), Vector(18.979, -1.209, 35.137),
			Vector(18.979, -9.209, 35.137)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-29.696, -7.773, 1.824), Vector(-10.335, -13, 37.932), Vector(1.988, -8.728, 8.998), Vector(
			23.650, -3, 34.224))[Global.ArenaID];
		Global.ArenaRadius = Array(18, 20, 25, 24)[Global.ArenaID];
		"66번 국도"
		Skip If(Current Map != Map(66번 국도), 5);
		Global.ArenaID = Random Integer(0, 3);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(-33.503, 10.480, 5.999), Vector(-30.159, 8.303, -17.153), Vector(-30.913, 3.308,
			-16.236), Vector(-11.459, 2.904, -2.950), Vector(-13.170, 3.902, 8.837), Vector(-39.985, 3.223, 0.831)), Array(Vector(-30.471,
			3.301, -22.592), Vector(-14.876, 3.551, -43.152), Vector(-37.495, 3.183, -39.266), Vector(-23.152, 8.277, -21.932), Vector(
			-41.064, 9.696, -43.343), Vector(-11.745, 8.410, -43.186)), Array(Vector(-81.588, 13.234, 11.863), Vector(-84.185, 6.374,
			7.966), Vector(-67.896, 10.375, -2.905), Vector(-63.226, 4.521, -1.001), Vector(-47.852, 5.446, 15.166), Vector(-68.340, 8.381,
			23.349)), Array(Vector(-106.758, 12.375, -27.190), Vector(-92.427, 6.420, -23.313), Vector(-74.402, 10.375, -6.125), Vector(
			-89.944, 9.908, 4.433), Vector(-106.317, 8.382, -14.988), Vector(-77.144, 6.381, 2.378)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-28.595, 9.949, 0.932), Vector(-24.965, 11.105, -36.186), Vector(-64.943, 5.500, 12.776), Vector(
			-92.138, 5.500, -13.454))[Global.ArenaID];
		Global.ArenaRadius = Array(22, 22, 24, 27)[Global.ArenaID];
		"볼스카야 인더스트리"
		Skip If(Current Map != Map(볼스카야 인더스트리), 5);
		Global.ArenaID = Random Integer(0, 3);
		Wait(0.016, Ignore Condition);
		Global.SphereLocations = Array(Array(Vector(-109.840, 2.268, 56.574), Vector(-107.029, -2.182, 38.410), Vector(-87.218, -2.232,
			33.859), Vector(-76.384, -1.732, 46.022), Vector(-101.492, -3.682, 63.548), Vector(-80.850, 0.175, 59.025)), Array(Vector(
			-31.732, -3.980, 95.989), Vector(-35.504, -3.802, 69.428), Vector(-47.155, -4.907, 94.092), Vector(-52.228, 2.020, 87.990),
			Vector(-32.224, 2.020, 72.108), Vector(-27.497, 2.020, 89.248)), Array(Vector(-71.110, -1.880, 49.570), Vector(-79.720, -1.750,
			63.040), Vector(-64.790, 2.620, 49.960), Vector(-69.570, -3.560, 74.240), Vector(-57.480, -4.060, 64.510), Vector(-76.580,
			2.970, 50.750)), Array(Vector(-20.436, -5.237, 30.779), Vector(-39.299, -2.980, 35.285), Vector(-43.850, 2.020, 28.468),
			Vector(-40.267, 2.954, 38.401), Vector(-36.675, -4.980, 15.760), Vector(-20.720, -6.983, 9.950)))[Global.ArenaID];
		Global.ArenaCentre = Array(Vector(-94.328, 0.527, 49.164), Vector(-37.830, -10, 83.524), Vector(-71.480, -2.330, 63.120), Vector(
			-32.391, -3.015, 22.929))[Global.ArenaID];
		Global.ArenaRadius = Array(26, 21, 20, 23)[Global.ArenaID];
		"자기장 효과"
		Create Effect(All Players(All Teams), Sphere, Color(흰색), Global.ArenaCentre, Global.ArenaRadius, Visible To);
	}
}

rule("[특전, 왕] 5라운드가 되면 특전 텍스트 지정됨 // 여기서 영웅별 텍스트를 입력하세요 (왕 특혜 수정, 0719)")
{
	event
	{
		Subroutine;
		TTEK_TRIGGER;
	}

	action
	{
		Players On Hero(Hero(둠피스트), All Teams).ttek_text[0] = Custom String("시간을 달려서 {0}", Ability Icon String(Hero(트레이서), Button(
			Ability 1)));
		Players On Hero(Hero(둠피스트), All Teams).ttek_text[1] = Custom String("시간 연장 횟수 3회 추가");
		Players On Hero(Hero(둠피스트), All Teams).ttek_text[2] = Custom String("그때 그 시절 {0}", Ability Icon String(Hero(둠피스트), Button(
			Ability 1)));
		Players On Hero(Hero(둠피스트), All Teams).ttek_text[3] = Custom String("지진 강타에 맞은 적을 1.25초간 넉다운시킴");
		Players On Hero(Hero(마우가), All Teams).ttek_text[0] = Custom String("피가 끓어오른다 {0}", Icon String(Fire));
		Players On Hero(Hero(마우가), All Teams).ttek_text[1] = Custom String("E키가 활성화 되며 E를 사용하는 동안 주변 적들에게 화상 상태 부여");
		Players On Hero(Hero(마우가), All Teams).ttek_text[2] = Custom String("쿵쾅쿵쾅 {0}", Hero Icon String(Hero(자리야)));
		Players On Hero(Hero(마우가), All Teams).ttek_text[3] = Custom String("돌파에 피격된 적이 1.5초간 넘어짐");
		Players On Hero(Hero(라마트라), All Teams).ttek_text[0] = Custom String("응징의 소용돌이 {0}", Ability Icon String(Hero(라마트라), Button(
			Ability 2)));
		Players On Hero(Hero(라마트라), All Teams).ttek_text[1] = Custom String("적들에게 스턴상태를 부여하는 탐식의 소용돌이 사용 가능");
		Players On Hero(Hero(라마트라), All Teams).ttek_text[2] = Custom String("화끈한 절멸 {0}", Icon String(Fire));
		Players On Hero(Hero(라마트라), All Teams).ttek_text[3] = Custom String("절멸 범위 내 적들에게 화상상태 부여");
		Players On Hero(Hero(로드호그), All Teams).ttek_text[0] = Custom String("신속의 물약 {0}", Hero Icon String(Hero(트레이서)));
		Players On Hero(Hero(로드호그), All Teams).ttek_text[1] = Custom String("우클릭 사용 시 이동속도가 2배가 됨");
		Players On Hero(Hero(로드호그), All Teams).ttek_text[2] = Custom String("치유의 물약 {0}", Hero Icon String(Hero(메르시)));
		Players On Hero(Hero(로드호그), All Teams).ttek_text[3] = Custom String("최대 수명이 5R 증가함");
		Players On Hero(Hero(라인하르트), All Teams).ttek_text[0] = Custom String("불망치 {0}", Icon String(Fire));
		Players On Hero(Hero(라인하르트), All Teams).ttek_text[1] = Custom String("기본 공격에 맞은 적군에게 화염 상태 부여");
		Players On Hero(Hero(라인하르트), All Teams).ttek_text[2] = Custom String("변화(火)구 {0}", Ability Icon String(Hero(라인하르트), Button(
			Ability 2)));
		Players On Hero(Hero(라인하르트), All Teams).ttek_text[3] = Custom String("화염 강타(E) 활성화");
		Players On Hero(Hero(해저드), All Teams).ttek_text[0] = Custom String("더 아픈 주사 {0}", Ability Icon String(Hero(해저드), Button(
			Secondary Fire)));
		Players On Hero(Hero(해저드), All Teams).ttek_text[1] = Custom String("불주사에 맞은 적을 넉백시킴");
		Players On Hero(Hero(해저드), All Teams).ttek_text[2] = Custom String("광역 속박 {0}", Ability Icon String(Hero(해저드), Button(Ultimate)));
		Players On Hero(Hero(해저드), All Teams).ttek_text[3] = Custom String("궁극기 사용 시 모든 적 속박");
		Players On Hero(Hero(레킹볼), All Teams).ttek_text[0] = Custom String("잔상 {0}", Ability Icon String(Hero(솜브라), Button(Ability 2)));
		Players On Hero(Hero(레킹볼), All Teams).ttek_text[1] = Custom String("상호작용 시 공중으로 순간이동 (쿨타임: 30초)");
		Players On Hero(Hero(레킹볼), All Teams).ttek_text[2] = Custom String("강화된 보호막 {0}", Ability Icon String(Hero(레킹볼), Button(
			Ability 2)));
		Players On Hero(Hero(레킹볼), All Teams).ttek_text[3] = Custom String("보호막을 사용하는 동안 피해를 받지 않음");
		Players On Hero(Hero(시그마), All Teams).ttek_text[0] = Custom String("공중부양 {0}", Ability Icon String(Hero(메르시), Button(Ability 1)));
		Players On Hero(Hero(시그마), All Teams).ttek_text[1] = Custom String("시그마가 공중부양할 수 있음 (단 공중부양하는 동안 이동속도 감소)");
		Players On Hero(Hero(시그마), All Teams).ttek_text[2] = Custom String("고중력 붕괴 {0}", Ability Icon String(Hero(시그마), Button(
			Ability 2)));
		Players On Hero(Hero(시그마), All Teams).ttek_text[3] = Custom String("SHIFT 사용 시 모두를 바닥으로 가라앉히고 넉다운 부여\n (더 이상 저중력 붕괴 사용불가)");
		Players On Hero(Hero(오리사), All Teams).ttek_text[0] = Custom String("공격 강화 {0}", Ability Icon String(Hero(오리사), Button(Ability 1)));
		Players On Hero(Hero(오리사), All Teams).ttek_text[1] = Custom String("투창 및 수호의 창 쿨타임이 30% 감소됨 (영구)");
		Players On Hero(Hero(오리사), All Teams).ttek_text[2] = Custom String("완전무적 {0}", Ability Icon String(Hero(오리사), Button(Ultimate)));
		Players On Hero(Hero(오리사), All Teams).ttek_text[3] = Custom String("완전무적 상태가 될 수 있는 궁극기 사용 가능 (1회)");
		Players On Hero(Hero(자리야), All Teams).ttek_text[0] = Custom String("포켓걸 자리야 {0}", Icon String(Heart));
		Players On Hero(Hero(자리야), All Teams).ttek_text[1] = Custom String("자리야가 주머니에 쏙♥ 들어갈 사이즈로 변경됨");
		Players On Hero(Hero(자리야), All Teams).ttek_text[2] = Custom String("깃털같은 몸짓 {0}", Ability Icon String(Hero(메르시), Button(Jump)));
		Players On Hero(Hero(자리야), All Teams).ttek_text[3] = Custom String("자리야의 이동 중력이 감소됨");
		Players On Hero(Hero(정커퀸), All Teams).ttek_text[0] = Custom String("흡혈 루트 {0}", Hero Icon String(Hero(정커퀸)));
		Players On Hero(Hero(정커퀸), All Teams).ttek_text[1] = Custom String("근접 공격으로 흡혈 가능 (쿨타임: 3초)");
		Players On Hero(Hero(정커퀸), All Teams).ttek_text[2] = Custom String("입체기동 톱니칼 II {0}", Ability Icon String(Hero(정커퀸), Button(
			Secondary Fire)));
		Players On Hero(Hero(정커퀸), All Teams).ttek_text[3] = Custom String("입체기동 톱니칼이 대폭 강화되지만, 도륙 사용 불가");
		Players On Hero(Hero(D.Va), All Teams).ttek_text[0] = Custom String("쏠 수 있어! {0}", Ability Icon String(Hero(캐서디), Button(
			Primary Fire)));
		Players On Hero(Hero(D.Va), All Teams).ttek_text[1] = Custom String("송하나가 총을 쏠 때 스턴 상태가 1/4로 단축됨");
		Players On Hero(Hero(D.Va), All Teams).ttek_text[2] = Custom String("에임 연습 {0}", Icon String(Flag));
		Players On Hero(Hero(D.Va), All Teams).ttek_text[3] = Custom String("송하나 빙글뱅글 5회 추가");
		Players On Hero(Hero(윈스턴), All Teams).ttek_text[0] = Custom String("자... 이게 클릭이야");
		Players On Hero(Hero(윈스턴), All Teams).ttek_text[1] = Custom String("좌클릭에 맞은 적에게 짧은 스턴 효과 부여");
		Players On Hero(Hero(윈스턴), All Teams).ttek_text[2] = Custom String("깔아뭉개기");
		Players On Hero(Hero(윈스턴), All Teams).ttek_text[3] = Custom String("점프팩에 맞은 적에게 넉다운 부여\r\n (점프팩 쿨타임 3배 증가)");
		Players On Hero(Hero(라이프위버), All Teams).ttek_text[0] = Custom String("아낌없이 주는 나무");
		Players On Hero(Hero(라이프위버), All Teams).ttek_text[1] = Custom String("궁극기 사용 시 자신의 궁극기 게이지 일정량이 주기적으로 증가함");
		Players On Hero(Hero(라이프위버), All Teams).ttek_text[2] = Custom String("단상이 좋아");
		Players On Hero(Hero(라이프위버), All Teams).ttek_text[3] = Custom String("연꽃 단상의 쿨타임이 15초가 됨");
		Players On Hero(Hero(루시우), All Teams).ttek_text[0] = Custom String("루풍참");
		Players On Hero(Hero(루시우), All Teams).ttek_text[1] = Custom String("SHIFT 사용 시 순간 가속");
		Players On Hero(Hero(루시우), All Teams).ttek_text[2] = Custom String("소리분쇄");
		Players On Hero(Hero(루시우), All Teams).ttek_text[3] = Custom String("궁 사용 시 범위 내 적에게 넉다운 부여");
		Players On Hero(Hero(메르시), All Teams).ttek_text[0] = Custom String("의사");
		Players On Hero(Hero(메르시), All Teams).ttek_text[1] = Custom String("타인 부활 +1");
		Players On Hero(Hero(메르시), All Teams).ttek_text[2] = Custom String("도박사");
		Players On Hero(Hero(메르시), All Teams).ttek_text[3] = Custom String("무빙의 개수가 랜덤이 됨");
		Players On Hero(Hero(모이라), All Teams).ttek_text[0] = Custom String("도트 빙결 II");
		Players On Hero(Hero(모이라), All Teams).ttek_text[1] = Custom String("도트 빙결의 지속시간이 3배 증가");
		Players On Hero(Hero(모이라), All Teams).ttek_text[2] = Custom String("50 대 50");
		Players On Hero(Hero(모이라), All Teams).ttek_text[3] = Custom String("생체구슬 사용 시 50% 확률로 쿨타임이 0초가 됨");
		Players On Hero(Hero(바티스트), All Teams).ttek_text[0] = Custom String("문워크 {0}", Ability Icon String(Hero(바티스트), Button(Ultimate)));
		Players On Hero(Hero(바티스트), All Teams).ttek_text[1] = Custom String("세일러문이 가장 가까운 플레이어를 따라다니게 됨");
		Players On Hero(Hero(바티스트), All Teams).ttek_text[2] = Custom String("300 {0}", Icon String(Recycle));
		Players On Hero(Hero(바티스트), All Teams).ttek_text[3] = Custom String("세일러문 게이지가 300만큼 증가됨");
		Players On Hero(Hero(브리기테), All Teams).ttek_text[0] = Custom String("쿨팩");
		Players On Hero(Hero(브리기테), All Teams).ttek_text[1] = Custom String("궁을 사용하지 않은 채 E를 쓰면 적을 얼림");
		Players On Hero(Hero(브리기테), All Teams).ttek_text[2] = Custom String("아빠 친구의 방패");
		Players On Hero(Hero(브리기테), All Teams).ttek_text[3] = Custom String("방패 크기 대폭 증가");
		Players On Hero(Hero(아나), All Teams).ttek_text[0] = Custom String("잘 시간이야 {0}", Ability Icon String(Hero(아나), Button(Ability 1)));
		Players On Hero(Hero(아나), All Teams).ttek_text[1] = Custom String("수면총 쿨타임이 50% 감소됨 (영구)");
		Players On Hero(Hero(아나), All Teams).ttek_text[2] = Custom String("금지약물 복용 {0}", Ability Icon String(Hero(로드호그), Button(
			Secondary Fire)));
		Players On Hero(Hero(아나), All Teams).ttek_text[3] = Custom String("궁극기 사용 시 자신의 속도가 빨라짐");
		Players On Hero(Hero(일리아리), All Teams).ttek_text[0] = Custom String("빠른 분출");
		Players On Hero(Hero(일리아리), All Teams).ttek_text[1] = Custom String("치명타 공격 적중 시 SHIFT 쿨타임 2배 감소");
		Players On Hero(Hero(일리아리), All Teams).ttek_text[2] = Custom String("빠른 태양 작렬");
		Players On Hero(Hero(일리아리), All Teams).ttek_text[3] = Custom String("치명타 공격 적중 시 궁극기 게이지 2배 증가");
		Players On Hero(Hero(젠야타), All Teams).ttek_text[0] = Custom String("걸음마");
		Players On Hero(Hero(젠야타), All Teams).ttek_text[1] = Custom String("초월 중 이동 가능");
		Players On Hero(Hero(젠야타), All Teams).ttek_text[2] = Custom String("깨달음");
		Players On Hero(Hero(젠야타), All Teams).ttek_text[3] = Custom String("수련 게이지 +40");
		Players On Hero(Hero(주노), All Teams).ttek_text[0] = Custom String("진짜 석양");
		Players On Hero(Hero(주노), All Teams).ttek_text[1] = Custom String("쁘띠 석양의 스턴 시간이 2배 증가");
		Players On Hero(Hero(주노), All Teams).ttek_text[2] = Custom String("하이퍼루프");
		Players On Hero(Hero(주노), All Teams).ttek_text[3] = Custom String("하이퍼 링 설치 시 이속 2~3배 증가");
		Players On Hero(Hero(키리코), All Teams).ttek_text[0] = Custom String("짭순보");
		Players On Hero(Hero(키리코), All Teams).ttek_text[1] = Custom String("궁을 사용하지 않은 채 SHIFT 사용 시 죽은 플레이어 위치로 이동");
		Players On Hero(Hero(키리코), All Teams).ttek_text[2] = Custom String("장난꾸러기");
		Players On Hero(Hero(키리코), All Teams).ttek_text[3] = Custom String("라운드 당 페이크셀 2개 설치 가능");
		Players On Hero(Hero(겐지), All Teams).ttek_text[0] = Custom String("광속 베기");
		Players On Hero(Hero(겐지), All Teams).ttek_text[1] = Custom String("즉시 궁을 사용하며 모든 적들의 용검 카운트 -1");
		Players On Hero(Hero(겐지), All Teams).ttek_text[2] = Custom String("유령화");
		Players On Hero(Hero(겐지), All Teams).ttek_text[3] = Custom String("궁극기 사용 시 3초간 무적상태가 됨");
		Players On Hero(Hero(리퍼), All Teams).ttek_text[0] = Custom String("장식이 아냐");
		Players On Hero(Hero(리퍼), All Teams).ttek_text[1] = Custom String("총을 쏠 수 있으며 맞은 적에게 스턴을 줌");
		Players On Hero(Hero(리퍼), All Teams).ttek_text[2] = Custom String("영혼 수확");
		Players On Hero(Hero(리퍼), All Teams).ttek_text[3] = Custom String("적이 죽을 때마다 궁 게이지 +30%");
		Players On Hero(Hero(메이), All Teams).ttek_text[0] = Custom String("Let it go {0}", Ability Icon String(Hero(메이), Button(
			Primary Fire)));
		Players On Hero(Hero(메이), All Teams).ttek_text[1] = Custom String("스프레이 150회를 추가로 획득함");
		Players On Hero(Hero(메이), All Teams).ttek_text[2] = Custom String("고드름 {0}", Ability Icon String(Hero(메이), Button(
			Secondary Fire)));
		Players On Hero(Hero(메이), All Teams).ttek_text[3] = Custom String("우클릭에 맞은 적에게 빙결상태 부여 (원거리 공격)");
		Players On Hero(Hero(바스티온), All Teams).ttek_text[0] = Custom String("설정: 급습 {0}", Ability Icon String(Hero(트레이서), Button(
			Ability 1)));
		Players On Hero(Hero(바스티온), All Teams).ttek_text[1] = Custom String("설정: 강습 상태일 때 이동속도가 빨라짐");
		Players On Hero(Hero(바스티온), All Teams).ttek_text[2] = Custom String("설정: 공습 {0}", Ability Icon String(Hero(바스티온), Button(
			Secondary Fire)));
		Players On Hero(Hero(바스티온), All Teams).ttek_text[3] = Custom String("설정: 강습 상태일 때 우클릭 무한으로 사용가능");
		Players On Hero(Hero(벤처), All Teams).ttek_text[0] = Custom String("땅속의 냄새");
		Players On Hero(Hero(벤처), All Teams).ttek_text[1] = Custom String("땅에 들어갔다 나오면 더러운 냄새를 풍겨 주변 적들을 기절시킴");
		Players On Hero(Hero(벤처), All Teams).ttek_text[2] = Custom String("야매강착");
		Players On Hero(Hero(벤처), All Teams).ttek_text[3] = Custom String("E키를 누르면 땅속에서 얻은 바위를 던짐 (쿨타임: 30초)");
		Players On Hero(Hero(소전), All Teams).ttek_text[0] = Custom String("분열 다이너마이트");
		Players On Hero(Hero(소전), All Teams).ttek_text[1] = Custom String("분열 사격으로 피해를 입은 적이 잠시 기절함");
		Players On Hero(Hero(소전), All Teams).ttek_text[2] = Custom String("슈퍼 파워 슬라이드");
		Players On Hero(Hero(소전), All Teams).ttek_text[3] = Custom String("파워 슬라이드를 사용하는 동안 이속이 빨라짐");
		Players On Hero(Hero(솔저: 76), All Teams).ttek_text[0] = Custom String("움직이면 게이 {0}", Hero Icon String(Hero(라이프위버)));
		Players On Hero(Hero(솔저: 76), All Teams).ttek_text[1] = Custom String("움직이지 않는 동안 무적 상태 (최대 10회)");
		Players On Hero(Hero(솔저: 76), All Teams).ttek_text[2] = Custom String("로켓 난사");
		Players On Hero(Hero(솔저: 76), All Teams).ttek_text[3] = Custom String("궁극기를 사용하는 동안 우클릭 쿨타임 무제한");
		Players On Hero(Hero(솜브라), All Teams).ttek_text[0] = Custom String("은신");
		Players On Hero(Hero(솜브라), All Teams).ttek_text[1] = Custom String("항상 은신 상태가 됨");
		Players On Hero(Hero(솜브라), All Teams).ttek_text[2] = Custom String("해킹");
		Players On Hero(Hero(솜브라), All Teams).ttek_text[3] = Custom String("적을 해킹할 수 있음");
		Players On Hero(Hero(시메트라), All Teams).ttek_text[0] = Custom String("냉온고문 {0}", Hero Icon String(Hero(토르비욘)));
		Players On Hero(Hero(시메트라), All Teams).ttek_text[1] = Custom String("버블버블을 맞은 적에게 화상 부여");
		Players On Hero(Hero(시메트라), All Teams).ttek_text[2] = Custom String("레이저제모 {0}", Hero Icon String(Hero(윈스턴)));
		Players On Hero(Hero(시메트라), All Teams).ttek_text[3] = Custom String("스턴 상태를 부여하는 좌클릭 활성화");
		Players On Hero(Hero(애쉬), All Teams).ttek_text[0] = Custom String("적응완료");
		Players On Hero(Hero(애쉬), All Teams).ttek_text[1] = Custom String("화상상태여도 이동속도가 감소하지 않음");
		Players On Hero(Hero(애쉬), All Teams).ttek_text[2] = Custom String("정밀한 저격");
		Players On Hero(Hero(애쉬), All Teams).ttek_text[3] = Custom String("치명타 공격 적중 시 1.5초 스턴");
		Players On Hero(Hero(에코), All Teams).ttek_text[0] = Custom String("원펀맨");
		Players On Hero(Hero(에코), All Teams).ttek_text[1] = Custom String("맞으면 바로 죽는 근접공격을 1회 할 수 있음");
		Players On Hero(Hero(에코), All Teams).ttek_text[2] = Custom String("점착 폭탄");
		Players On Hero(Hero(에코), All Teams).ttek_text[3] = Custom String("즉시 우클릭이 써짐\r\n (양자택일 우클릭 선택 시에만 작동)");
		Players On Hero(Hero(위도우메이커), All Teams).ttek_text[0] = Custom String("스파이더 킥 {0}", Ability Icon String(Hero(위도우메이커), Button(
			Ability 2)));
		Players On Hero(Hero(위도우메이커), All Teams).ttek_text[1] = Custom String("갈고리 이동 동선에 있는 적들을 넉다운시킴");
		Players On Hero(Hero(위도우메이커), All Teams).ttek_text[2] = Custom String("신화 각성 {0}", Icon String(Fire));
		Players On Hero(Hero(위도우메이커), All Teams).ttek_text[3] = Custom String("12라운드부터 공격 당한 적의 빙결시간이 4배가 됨");
		Players On Hero(Hero(정크랫), All Teams).ttek_text[0] = Custom String("폭탄 발사!");
		Players On Hero(Hero(정크랫), All Teams).ttek_text[1] = Custom String("넉백을 주는 기본 공격 활성화");
		Players On Hero(Hero(정크랫), All Teams).ttek_text[2] = Custom String("올타임 피버 타임");
		Players On Hero(Hero(정크랫), All Teams).ttek_text[3] = Custom String("충격 지뢰 무제한 사용 가능");
		Players On Hero(Hero(캐서디), All Teams).ttek_text[0] = Custom String("구르기 장인");
		Players On Hero(Hero(캐서디), All Teams).ttek_text[1] = Custom String("구를 때 잠시 무적이 됨");
		Players On Hero(Hero(캐서디), All Teams).ttek_text[2] = Custom String("석양이 없다");
		Players On Hero(Hero(캐서디), All Teams).ttek_text[3] = Custom String("더이상 궁을 쓸 수 없지만 매 라운드 시작 전에 100%의 궁 게이지를 받음");
		Players On Hero(Hero(토르비욘), All Teams).ttek_text[0] = Custom String("용암 뿌리기");
		Players On Hero(Hero(토르비욘), All Teams).ttek_text[1] = Custom String("궁극기 사용 가능\r\n (1번 무기를 들고 쓰면 스턴 / 2번 무기를 들고 쓰면 넉백)");
		Players On Hero(Hero(토르비욘), All Teams).ttek_text[2] = Custom String("길어진 다리");
		Players On Hero(Hero(토르비욘), All Teams).ttek_text[3] = Custom String("캐릭터 크기가 커지고 짧은다리 패시브가 없어짐");
		Players On Hero(Hero(트레이서), All Teams).ttek_text[0] = Custom String("임펄스 쌍권총");
		Players On Hero(Hero(트레이서), All Teams).ttek_text[1] = Custom String("맞은 적에게 넉백을 주는 기본공격 사용 가능");
		Players On Hero(Hero(트레이서), All Teams).ttek_text[2] = Custom String("체력 역행");
		Players On Hero(Hero(트레이서), All Teams).ttek_text[3] = Custom String("체력이 다시 풀피가 됨");
		Players On Hero(Hero(파라), All Teams).ttek_text[0] = Custom String("공습 작전");
		Players On Hero(Hero(파라), All Teams).ttek_text[1] = Custom String("맞은 적에게 넉다운을 주는 기본공격 사용 가능");
		Players On Hero(Hero(파라), All Teams).ttek_text[2] = Custom String("이래야 파라지");
		Players On Hero(Hero(파라), All Teams).ttek_text[3] = Custom String("점프 추진기 사용 가능");
		Players On Hero(Hero(한조), All Teams).ttek_text[0] = Custom String("시마다 형제 {0}", Hero Icon String(Hero(겐지)));
		Players On Hero(Hero(한조), All Teams).ttek_text[1] = Custom String("겐지의 은신 패시브가 적용됨");
		Players On Hero(Hero(한조), All Teams).ttek_text[2] = Custom String("미래를 보는 눈");
		Players On Hero(Hero(한조), All Teams).ttek_text[3] = Custom String("즉시 궁극기를 사용함");
		Players On Hero(Hero(프레야), All Teams).ttek_text[0] = Custom String("정밀한 화살");
		Players On Hero(Hero(프레야), All Teams).ttek_text[1] = Custom String("맞은 적들에게 짧은 스턴 부여");
		Players On Hero(Hero(프레야), All Teams).ttek_text[2] = Custom String("빠른 조준");
		Players On Hero(Hero(프레야), All Teams).ttek_text[3] = Custom String("조준하는 동안 이동속도 증가");
		If(Global.king_triggered == 2);
			Filtered Array(All Players(All Teams), Current Array Element.was_kinged != True).ttek_trigger = True;
	}
}

rule("[특전] 모든 특전 선택됨 (왕)")
{
	event
	{
		Subroutine;
		TTEK_KING;
	}

	action
	{
		Destroy HUD Text(Global.KING.ttek_effect[0]);
		Destroy HUD Text(Global.KING.ttek_effect[1]);
		Destroy HUD Text(Global.KING.ttek_effect[2]);
		Destroy HUD Text(Global.KING.ttek_effect[3]);
		Global.KING.ttek_effect = Null;
		Skip If(Global.KING.ttek_left_enable == True, 3);
		Global.KING.ttek_left_enable = True;
		Create HUD Text(Global.KING, Null, Custom String("   "), Null, Left, 40, Color(Green), Color(Green), Color(흰색), None,
			Default Visibility);
		Create HUD Text(Global.KING, Custom String("{0} 특전", Icon String(Asterisk)), Null, Custom String(" '{2}'\n {1}",
			Input Binding String(Button(Primary Fire)), Global.KING.ttek_text[1], Global.KING.ttek_text[0]), Left, 41, Color(Orange),
			Color(흰색), Color(흰색), None, Default Visibility);
		Skip If(Global.KING.ttek_right_enable == True, 3);
		Global.KING.ttek_right_enable = True;
		Create HUD Text(Global.KING, Null, Custom String("   "), Null, Left, 42, Color(Green), Color(Green), Color(흰색), None,
			Default Visibility);
		Create HUD Text(Global.KING, Custom String("{0} 특전", Icon String(Asterisk)), Null, Custom String(" '{2}'\n {1}",
			Input Binding String(Button(Secondary Fire)), Global.KING.ttek_text[3], Global.KING.ttek_text[2]), Left, 43, Color(Orange),
			Color(흰색), Color(흰색), None, Default Visibility);
	}
}

rule("[왕] Is Game In Porgress 후 랜덤으로 왕 결정됨")
{
	event
	{
		Ongoing - Global;
	}

	action
	{
		Wait Until(Is Game In Progress, 99999);
		Global.KING = Random Value In Array(All Players(All Teams));
	}
}

rule("[왕] 왕 결정 (첫 스폰)")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Has Spawned(Global.KING) == True;
		Is Alive(Global.KING) == True;
		Global.king_triggered == 0;
	}

	action
	{
		Global.king_triggered = 1;
		Call Subroutine(TTEK_TRIGGER);
		Call Subroutine(TTEK_KING);
		Global.KING.was_kinged = True;
		Big Message(Global.KING, Custom String("{0} 당신은 왕입니다! 모든 특전이 자동으로 선택됩니다!", Icon String(Fire)));
	}
}

rule("[특전] 특전 활성화 조건 - 5라운드 (왕이었던 사람 제외)")
{
	event
	{
		Ongoing - Global;
	}

	condition
	{
		Global.RoundNumber == 5;
	}

	action
	{
		Global.king_triggered = 2;
		Start Rule(TTEK_TRIGGER, Restart Rule);
	}
}

rule("[왕] 왕 Text")
{
	event
	{
		Ongoing - Each Player;
		All;
		All;
	}

	action
	{
		Create HUD Text(Event Player, Null, Null, Custom String("{0} 왕: {1} {2}", Icon String(Fire), Global.KING, Hero Icon String(Hero Of(
			Global.KING))), Right, 1.004, Color(흰색), Color(흰색), Color(Rose), Visible To and String, Default Visibility);
	}
}

rule("[왕] 왕 교체: 죽음")
{
	event
	{
		Player Died;
		All;
		All;
	}

	condition
	{
		Global.KING == Event Player;
	}

	action
	{
		Wait(0.500, Ignore Condition);
		If(Is Alive(Attacker));
			Global.KING = Attacker;
			Big Message(Filtered Array(All Players(All Teams), Current Array Element != Global.KING), Custom String("{0} 왕이 교체됩니다!",
				Icon String(Fire)));
		Else;
			Global.KING = Random Value In Array(Global.LivingPlayers);
			Big Message(Filtered Array(All Players(All Teams), Current Array Element != Global.KING), Custom String("{0} 랜덤으로 왕이 결정됩니다!",
				Icon String(Fire)));
		End;
		Global.king_triggered = 1;
		Call Subroutine(TTEK_TRIGGER);
		Call Subroutine(TTEK_KING);
		Global.KING.was_kinged = True;
		Big Message(Global.KING, Custom String("{0} 당신은 왕입니다! 모든 특전이 자동으로 선택됩니다!", Icon String(Fire)));
	}
}

rule("[왕] 왕 교체: 나감")
{
	event
	{
		Player Left Match;
		All;
		All;
	}

	condition
	{
		Event Player == Global.KING;
	}

	action
	{
		Wait(0.500, Ignore Condition);
		Global.KING = Random Value In Array(Global.LivingPlayers);
		Big Message(Filtered Array(All Players(All Teams), Current Array Element != Global.KING), Custom String("{0} 랜덤으로 왕이 결정됩니다!",
			Icon String(Fire)));
		Global.king_triggered = 1;
		Global.KING.was_kinged = True;
		Call Subroutine(TTEK_TRIGGER);
		Call Subroutine(TTEK_KING);
		Big Message(Global.KING, Custom String("{0} 당신은 왕입니다! 모든 특전이 자동으로 선택됩니다!", Icon String(Fire)));
	}
}