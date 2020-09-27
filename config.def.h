/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 25;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack Nerd Font:style=Regular:size=10" };
static const char dmenufont[]       = "Hack Nerd Font:style=Regular:size=10";
static const char col_gray1[]       = "#222222";	//Mas oscuro
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";	//Mas claro
static const char col_cyan[]        = "#005577";
static const char col1[]            = "#ff00ff";	//Rosa
static const char col2[]            = "#3341ff";	//Celeste
static const char col3[]            = "#000082";	//Dark Blue
static const char col4[]            = "#4300a2";	//Casi Violeta
static const char col5[]            = "#5d00a4";	//Dark Rose
static const char col6[]            = "#ffffff";
static const char col7[]            = "#ffffff";
static const char col8[]            = "#ffffff";
static const char col9[]            = "#ffffff";
static const char col10[]           = "#ffffff";
static const char col11[]           = "#ffffff";
static const char col12[]           = "#ffffff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]  = { col_gray4, col5,       col1 },
	[SchemeCol1]  = { col1,      col_gray1, col_gray2 },
	[SchemeCol2]  = { col2,      col_gray1, col_gray2 },
	[SchemeCol3]  = { col3,      col_gray1, col_gray2 },
	[SchemeCol4]  = { col4,      col_gray1, col_gray2 },
	[SchemeCol5]  = { col5,      col_gray1, col_gray2 },
	[SchemeCol6]  = { col6,      col_gray1, col_gray2 },
	[SchemeCol7]  = { col7,      col_gray1, col_gray2 },
	[SchemeCol8]  = { col8,      col_gray1, col_gray2 },
	[SchemeCol9]  = { col8,      col_gray1, col_gray2 },
	[SchemeCol10] = { col10,     col_gray1, col_gray2 },
	[SchemeCol11] = { col11,     col_gray1, col_gray2 },
	[SchemeCol12] = { col12,     col_gray1, col_gray2 },
	[SchemeSel]   = { col_gray4, col2,	col2  },	//prueba
//	[SchemeSel]   = { col_gray4, col_cyan,  col_cyan  },

};

/* tagging */
static const char *tags[] = { "", "", "阮", "切", "פּ", "龍", "", "[]", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
//	Check window class, instance and stuff with xprop
	/* class      instance    title       	tags mask     	isfloating   	monitor */
//	{ "Gimp",     NULL,       NULL,       	0,            	1,           	-1 },
	{ "firefox",  NULL,       NULL,       	2,     	    	0,           	-1 },
	{ "firefox",  NULL,       "Library",   	2,     	    	1,           	-1 },
	{ "zoom",     NULL,       NULL,       	1 << 4,	    	0,           	-1 },
	{ "zoom",     NULL,      "Zoom Meeting",1 << 5,	    	0,           	-1 },
	{ "Rambox",   NULL,       NULL,       	1 << 3,	    	0,           	-1 },
	{ NULL,	      "lutris",   NULL,       	1 << 6,	    	0,           	-1 },
	{ "Spotify",  "spotify",  NULL,	      	1 << 2,	    	0,		-1 },
	{ "Steam",   NULL,        NULL,       	1 << 6,	    	1,		-1 },
	{ "Steam",   NULL,"Friends List",       1 << 6,	    	1,		-1 },
	{ "Steam",   NULL,"Steam - News",     	1 << 6,	    	1,		-1 },
	{ "Gimp",    NULL,       NULL,       	1 << 5,     	0,           	-1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "terminator", NULL };
/*static const char *termcmd[]  = { "st", NULL };*/

static const char *playpause[]	    = { "playerctl", "play-pause"}; /* Play */
static const char *nextctl[]	    = { "playerctl", "next"};	/* Next Song */
static const char *previousctl[]    = { "playerctl", "previous"}; /* Prev Song */
static const char *toshutdown[]	    = { "prompt", "Sure you want to shut down?", "shutdown now"};
static const char *tosuspend[]	    = { "prompt", "Suspend sir?", "systemctl suspend"};
static const char *tolock[]	    = { "dm-tool", "lock"}; /* Locks the screen with LightDM */
static const char *touchpadoff[]    = { "touchpadoff"};		/*Turns the touchpad "off" */

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,              XF86XK_AudioLowerVolume, spawn, 	   SHCMD("pactl set-sink-volume 0 -10%; sigdwmblocks 5") },
	{ 0,              XF86XK_AudioMute,	   spawn, 	   SHCMD("pactl set-sink-mute 0 toggle; sigdwmblocks 5") },
	{ 0,              XF86XK_AudioRaiseVolume, spawn, 	   SHCMD("pactl set-sink-volume 0 +10%; sigdwmblocks 5") },
	{ 0,              XF86XK_AudioPlay,	   spawn, 	   {.v = playpause } },
	{ 0,              XF86XK_AudioPrev,	   spawn, 	   {.v = previousctl } },
	{ 0,              XF86XK_AudioNext,	   spawn, 	   {.v = nextctl } },
	{ 0,              XF86XK_MonBrightnessUp,  spawn, 	   SHCMD("brightnessctl -q s +10%; sigdwmblocks 3") },
	{ 0,              XF86XK_MonBrightnessDown,spawn, 	   SHCMD("brightnessctl -q s 10%-; sigdwmblocks 3") },
	{ 0,				XK_Print,  spawn,	   SHCMD("scrot ~/Pictures/Screenshots/Screenshot_-%Y-%m-%d_%H-%M.png") },
	{ MODKEY,			XK_Print,  spawn,	   SHCMD("scrot ~/Pictures/Screenshots/Screenshot_-%Y-%m-%d_%H-%M.png -e 'pcmanfm ~/Pictures/Screenshots/'") },
	{ MODKEY,             		XK_q,      killclient,     {0} }, //Kills a window
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} }, //Kills dwm
	{ MODKEY,             		XK_w,      spawn,	   {.v = toshutdown } },
	{ MODKEY,             		XK_e,      spawn,	   {.v = tosuspend } },
//	{ MODKEY,             		XK_r,      ,		   {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
//	{ MODKEY,             		XK_y,      ,		   {0} },
//	{ MODKEY,             		XK_u,      ,		   {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
//	{ MODKEY,             		XK_o,      ,		   {0} },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
//	{ MODKEY,             		XK_a,      ,		   {0} },
//	{ MODKEY,             		XK_s,      ,		   {0} },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
//	{ MODKEY,             		XK_g,      ,		   {0} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,    		XK_l,      spawn,	   {.v = tolock } },
	{ MODKEY,             		XK_z,      spawn,	   {.v = touchpadoff } },
//	{ MODKEY,             		XK_x,      ,		   {0} },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          SHCMD("xkill")},
//	{ MODKEY,             		XK_c,      ,		   {0} },
//	{ MODKEY,             		XK_v,      ,		   {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
//	{ MODKEY,             		XK_n,      ,		   {0} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },

	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },

	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
/* Button1 left click, Button2 middle click, Button 3 right click */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

