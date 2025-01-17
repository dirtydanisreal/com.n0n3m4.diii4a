package com.karin.idTech4Amm.sys;

import com.karin.idTech4Amm.R;
import com.n0n3m4.q3e.Q3EGlobals;

// game config
// config this can change launcher's game mod list.
public enum Game
{
    // DOOM 3
    DOOM3_BASE(Q3EGlobals.GAME_DOOM3, "base", "", "", false, R.string.doom_iii),
    DOOM3_D3XP(Q3EGlobals.GAME_DOOM3, "d3xp", "d3xp", "", true, R.string.doom3_resurrection_of_evil_d3xp),
    DOOM3_CDOOM(Q3EGlobals.GAME_DOOM3, "cdoom", "cdoom", "", true, R.string.classic_doom_cdoom),
    DOOM3_D3LE(Q3EGlobals.GAME_DOOM3, "d3le", "d3le", "d3xp", true, R.string.doom3_bfg_the_lost_mission_d3le),
    DOOM3_RIVENSIN(Q3EGlobals.GAME_DOOM3, "rivensin", "rivensin", "", true, R.string.rivensin_rivensin),
    DOOM3_HARDCORPS(Q3EGlobals.GAME_DOOM3, "hardcorps", "hardcorps", "", true, R.string.hardcorps_hardcorps),

    DOOM3_OVERTHINKED(Q3EGlobals.GAME_DOOM3, "overthinked", "overthinked", "", true, R.string.overthinked_doom_3),
    DOOM3_SABOT(Q3EGlobals.GAME_DOOM3, "sabot", "sabot", "d3xp", true, R.string.stupid_angry_bot_a7x),
    DOOM3_HEXENEOC(Q3EGlobals.GAME_DOOM3, "hexeneoc", "hexeneoc", "", true, R.string.hexen_edge_of_chaos),
    DOOM3_FRAGGINGFREE(Q3EGlobals.GAME_DOOM3, "fraggingfree", "fraggingfree", "d3xp", true, R.string.fragging_free),

    // Quake 4
    QUAKE4_BASE(Q3EGlobals.GAME_QUAKE4, "q4base", "", "", false, R.string.quake_iv_q4base),

    // Prey(2006)
    PREY_BASE(Q3EGlobals.GAME_PREY, "preybase", "", "", false, R.string.prey_preybase),
    ;

    public final String type; // game type: doom3/quake4/prey2006
    public final String game; // game id: unique
    public final String fs_game; // game data folder name
    public final String fs_game_base; // game mod data base folder name
    public final boolean is_mod; // is a mod
    public final Object name; // game name string resource's id or game name string

    Game(String type, String game, String fs_game, String fs_game_base, boolean is_mod, Object name)
    {
        this.type = type;
        this.game = game;
        this.fs_game = fs_game;
        this.fs_game_base = fs_game_base;
        this.is_mod = is_mod;
        this.name = name;
    }
}
