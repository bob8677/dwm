/* See LICENSE file for copyright and license details. */

/* appearance */
#include "/home/kyle/.cache/wal/colors-wal-dwm.h"

static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "FiraMono-Bold:size=10", "FiraCode Nerd Font Mono:size=12" };
static const unsigned int gappih 	    = 10;
static const unsigned int gappiv 	    = 10;
static const unsigned int gappoh 	    = 10;
static const unsigned int gappov 	    = 20;
static const int smartgaps 	   	    = 0; /* ONLY 1 OR 0 !!!!! */

/* tagging */
static const char *tags[] = { "爵", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "Weather", NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "shiftview.c"
#include "fibonacci.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "[D]",      deck },
};


/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define XF86MonBrightnessUp 0x1008ff02
#define XF86MonBrightnessDown 0x1008ff03
#define XF86AudioMute 0x1008ff12
#define XF86AudioLowerVolume 0x1008ff11
#define XF86AudioRaiseVolume 0x1008ff13
#define XF86AudioPrev 0x1008ff16
#define XF86AudioNext 0x1008ff17
#define XF86AudioPlay 0x1008ff14
#define XF86AudioPause 0x1008ff31

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */

static const char term[] = "st";
static const char sigblocks[] = "/home/kyle/packages/dwmblocks/sigdwmblocks";

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { &term[0], NULL };

static const char *cmdbrightup[] = { "brightnessctl", "set", "+10%", NULL };
static const char *cmdbrightdown[] = { "brightnessctl", "set", "10%-", NULL };

static const char *cmdaudioup[] = { "amixer", "-D", "pulse", "sset", "Master", "10%+", "unmute", NULL };
static const char *cmdaudiodown[] = { "amixer", "-D", "pulse", "sset", "Master", "10%-", "unmute", NULL };
static const char *cmdaudiomute[] = { "amixer", "-D", "pulse", "sset", "Master", "toggle", NULL };

static const char *cmdplaypause[] = { "playerctl", "-a", "play-pause", NULL };
static const char *cmdnext[] = { "playerctl", "-a", "next", NULL };
static const char *cmdprevious[] = { "playerctl", "-a", "previous", NULL };

static const char *cmddismiss[] = { "dismiss.sh" };
static const char *cmdsummon[] = { "summon.sh" };

static const char *runytop[] = { &term[0], "ytop", NULL };
static const char *runranger[] = { &term[0], "ranger", NULL };
static const char *runfirefox[] = { "firefox", NULL };
static const char *runflameshot[] = { "flameshot", "gui", "-p", "/home/kyle/Pictures/screenshots", NULL };
static const char *runmpvgui[] = { "mpv", "--player-operation-mode=pseudo-gui", "--keep-open=yes", NULL };
static const char *runnewsboat[] = { &term[0], "newsboat", NULL };
static const char *runweather[] = { &term[0], "-g", "126x41-455+200", "-c", "Weather", "weather.sh", NULL };

static const char *updatevol[] = { &sigblocks[0], "1", "1", NULL };

static const char *cmdexit[] = { "exit.sh" };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_semicolon, spawn,       {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_n,      spawn,          {.v = runnewsboat } },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = runytop } },
	{ MODKEY,                       XK_m,      spawn,          {.v = runmpvgui } },
	{ MODKEY,                       XK_comma,  spawn,          {.v = runfirefox } },
	{ MODKEY,                       XK_period, spawn,          {.v = runflameshot } },
	{ MODKEY|ShiftMask,             XK_period, spawn,          {.v = runweather } },
	{ MODKEY,                       XK_e,      spawn,          {.v = runranger } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_w,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_q,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.02} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.02} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_i,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_h,      focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,      focusmon,       {.i = +1 } },
	{ MODKEY|ControlMask,           XK_h,      tagmon,         {.i = -1 } },
	{ MODKEY|ControlMask,           XK_l,      tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask, 	        XK_k,      incrogaps,      {.i = +3 } },
	{ MODKEY|ShiftMask,  	        XK_j,      incrogaps,      {.i = -3 } },
	{ MODKEY|ControlMask,	        XK_k,      incrigaps,      {.i = +2 } },
	{ MODKEY|ControlMask, 	        XK_j,      incrigaps,      {.i = -2 } },
	{ MODKEY, 	                XK_g,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,  		XK_g,      defaultgaps,    {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ 0, 				XF86MonBrightnessUp, spawn, {.v = cmdbrightup } },
	{ 0, 				XF86MonBrightnessDown, spawn, {.v = cmdbrightdown } },
	{ 0, 				XF86AudioMute, spawn,      {.v = cmdaudiomute } },
	{ 0, 				XF86AudioMute, spawn,      {.v = updatevol } },
	{ 0, 				XF86AudioRaiseVolume, spawn, {.v = cmdaudioup } },
	{ 0, 				XF86AudioRaiseVolume, spawn, {.v = updatevol } },
	{ 0, 				XF86AudioLowerVolume, spawn, {.v = cmdaudiodown } },
	{ 0, 				XF86AudioLowerVolume, spawn, {.v = updatevol } },
	{ 0, 				XF86AudioPlay, spawn,      {.v = cmdplaypause } },
	{ 0, 				XF86AudioPause, spawn,     {.v = cmdplaypause } },
	{ 0, 				XF86AudioNext, spawn,      {.v = cmdnext } },
	{ 0, 				XF86AudioPrev, spawn,      {.v = cmdprevious } },
	{ MODKEY,                       XK_s,      spawn,          {.v = cmdsummon } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = cmddismiss } },
	{ MODKEY,                       XK_Escape, spawn,          {.v = cmdexit } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

