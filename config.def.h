/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 0;        /* gaps between windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack Nerd Font:style=Regular:size=11" };
static const char dmenufont[]       = "Hack Nerd Font:style=Regular:size=10";
static const char col_gray1[]       = "#222222";	//Mas oscuro
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";	//Mas claro
static const char col_cyan[]        = "#005577";
static const char colPink[]         = "#E634EC";	
static const char colCyan[]         = "#08949B";	
static const char colBlack[]        = "#000b1e";	
static const char colPurple[]       = "#4300a2";	
static const char colMagenta[]      = "#8A039E";	
static const char colYellow[]       = "#f57800";	
static const char colBlue[]         = "#123e7c";	
static const char colWhite[]        = "#FAB8FB";	
static const char colRed[]          = "#ff0000";	
static const char colGreen[]        = "#E634EC";
static const char col11[]           = "#ffffff";
static const char col12[]           = "#ffffff";
//Link to the color palette for reference
//https://coolors.co/005577-e634ec-08949b-000b1e-4300a2-8a039e-f57800-123e7c-fab8fb-ff0000
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]  = { colBlack,	colPink,	colCyan },	//Colores de Barra
	[SchemeCol1]  = { colPink,	col_gray1,	col_gray2 },
	[SchemeCol2]  = { colCyan,	col_gray1,	col_gray2 },
	[SchemeCol3]  = { colBlack,	col_gray1,	col_gray2 },
	[SchemeCol4]  = { colPurple,	col_gray1,	col_gray2 },
	[SchemeCol5]  = { colMagenta,	col_gray1,	col_gray2 },
	[SchemeCol6]  = { colYellow,	col_gray1,	col_gray2 },
	[SchemeCol7]  = { colBlue,	col_gray1,	col_gray2 },
	[SchemeCol8]  = { colWhite,	col_gray1,	col_gray2 },
	[SchemeCol9]  = { colRed,	col_gray1,	col_gray2 },
	[SchemeCol10] = { colGreen,	col_gray1,	col_gray2 },
	[SchemeCol11] = { col11,	col_gray1,	col_gray2 },
	[SchemeCol12] = { col12,	col_gray1,	col_gray2 },
	[SchemeSel]   = { colPurple,	colCyan,	colCyan  },	 //Ventana acutal y selecciones

};

/* tagging */
static const char *tags[] = { "", "", "阮", "切", "פּ", "龍", "", "[]"}; //Characters from the NERD font, they wont show on github

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
//	Check window class, instance and stuff with xprop
	/* class      	instance	    title       	tags mask     	isfloating   	monitor */
//	{ "Gimp",     	NULL,       	NULL,       	0,            	1,           	-1 },
	{ "firefox",  	NULL,       	NULL,       	2,     	    	0,           	-1 },
	{ "firefox",  	NULL,       	"Library",   	2,     	    	1,           	-1 },
	{ "zoom",     	NULL,       	NULL,       	1 << 4,	    	0,           	-1 },
	{ "zoom",    	NULL,      		"Zoom Meeting",	1 << 5,	    	0,           	-1 },
	{ "Rambox",   	NULL,       	NULL,       	1 << 3,	    	0,           	-1 },
	{ NULL,	  	"lutris",   	NULL,       	1 << 6,	    	0,           	-1 },
	{ "Spotify",  	"spotify",  	NULL,	      	1 << 2,	    	0,			-1 },
	{ "Steam",    	NULL,       	NULL,       	1 << 6,	    	1,			-1 },
	{ "Steam",    	NULL,			"Friends List",  	1 << 6,	    	1,			-1 },
	{ "Steam",    	NULL,			"Steam - News",	1 << 6,	    	1,			-1 },
	{ "Gimp",     	NULL,       	NULL,       	1 << 5,     	0,           	-1 },
	{ "Pavucontrol",  "pavucontrol",	NULL,			0,			1,			-1 },
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
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,              KEY,      tagnextmon,     {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask|ShiftMask,    KEY,      tagprevmon,     {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *browsercmd[] = { "firefox", NULL };
/*static const char *termcmd[]  = { "st", NULL };*/

static const char *playpause[]	= { "playerctl", "play-pause" };	/* Play */
static const char *nextctl[]		= { "playerctl", "next" };	/* Next Song */
static const char *previousctl[]    = { "playerctl", "previous" }; /* Prev Song */
//static const char *toshutdown[]	= { "prompt", "Sure you want to shut down?", "shutdown now" };
static const char *tosuspend[]	= { "prompt", "Suspend sir?", "systemctl suspend" };
static const char *tolock[]		= { "dm-tool", "lock" }; 	/* Locks the screen with LightDM */
static const char *touchpadoff[]	= { "touchpadoff" };		/* Turns the touchpad off */
static const char *screenshot[]	= { "scrot", "Screenshot_-%Y-%m-%d_%H-%M.png", "-e", "mv", "$f", "~/Pictures/Screenshots/" }; /* Simple screenshot */

static Key keys[] = {
	/* modifier			key		function	argument */
	{ 0,              XF86XK_AudioLowerVolume, 	spawn, 	SHCMD("pactl set-sink-volume 0 -10%; sigdwmblocks 5") },
	{ 0,              XF86XK_AudioMute,		spawn, 	SHCMD("pactl set-sink-mute 0 toggle; sigdwmblocks 5") },
	{ 0,              XF86XK_AudioRaiseVolume, 	spawn, 	SHCMD("pactl set-sink-volume 0 +10%; sigdwmblocks 5") },
	{ 0,              XF86XK_AudioPlay,		spawn, 	{.v = playpause } },
	{ 0,              XF86XK_AudioPrev,		spawn, 	{.v = previousctl } },
	{ 0,              XF86XK_AudioNext,		spawn, 	{.v = nextctl } },
	{ 0,              XF86XK_MonBrightnessUp,	spawn, 	SHCMD("brightnessctl -q s +10%; sigdwmblocks 3") },
	{ 0,              XF86XK_MonBrightnessDown,	spawn, 	SHCMD("brightnessctl -q s 10%-; sigdwmblocks 3") },
//	{ 0,				XK_Print,	spawn,		SHCMD("scrot ~/Pictures/Screenshots/Screenshot_-%Y-%m-%d_%H-%M.png") },
	{ 0,				XK_Print,	spawn, 	{.v = screenshot } },
//	{ MODKEY,			XK_Print,	spawn,	SHCMD("scrot ~/Pictures/Screenshots/Screenshot_-%Y-%m-%d_%H-%M.png -e 'pcmanfm ~/Pictures/Screenshots/'") },
	{ MODKEY,			XK_Print,	spawn,	SHCMD("scrot ~/Pictures/Screenshots/Screenshot_-%Y-%m-%d_%H-%M.png -e 'viewnior $f'") },
	{ MODKEY,			XK_q,		killclient,     {0} }, //Kills a window
	{ MODKEY|ShiftMask,             XK_q,		quit,           {0} }, //Kills dwm
	{ MODKEY,			XK_w,		spawn,	   SHCMD("sessionprompt") },
	{ MODKEY,			XK_e,		spawn,	   {.v = tosuspend } },
//	{ MODKEY,			XK_r,		,		   {0} },
	{ MODKEY,			XK_t,		setlayout,      {.v = &layouts[0]} },
//	{ MODKEY,			XK_y,		,		   {0} },
//	{ MODKEY,			XK_u,		,		   {0} },
	{ MODKEY,                       XK_i,		incnmaster,     {.i = +1 } },
//	{ MODKEY,			XK_o,		,		   {0} },
	{ MODKEY,                       XK_p,		spawn,          {.v = dmenucmd } },
	{ MODKEY,			XK_a,		spawn,		{.v = browsercmd } },
//	{ MODKEY,			XK_s,		,		   {0} },
	{ MODKEY,                       XK_d,		incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_f,		setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_f,		togglefullscr,  {0} },
//	{ MODKEY,			XK_g,		,		   {0} },
	{ MODKEY,                       XK_h,		setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_j,		focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,		focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_l,		setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,		XK_l,		spawn,	   {.v = tolock } },
	{ MODKEY,			XK_z,		spawn,	   {.v = touchpadoff } },
//	{ MODKEY,			XK_x,		,		   {0} },
	{ MODKEY|ShiftMask,             XK_x,		spawn,          SHCMD("xkill")},
//	{ MODKEY,			XK_c,		,		   {0} },
//	{ MODKEY,			XK_v,		,		   {0} },
	{ MODKEY,                       XK_b,		togglebar,      {0} },
	{ MODKEY,			XK_n,		spawn,	   SHCMD("networkmanager_dmenu")},
	{ MODKEY,                       XK_m,		setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_Return,	spawn,          {.v = termcmd } },

	{ MODKEY,                       XK_Return,	zoom,           {0} },
	{ MODKEY,                       XK_Tab,		view,           {0} },

	{ MODKEY,                       XK_space,	setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,	togglefloating, {0} },
	{ MODKEY,                       XK_0,		view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,		tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,	focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,	focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,	tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,	tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,	setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,	setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,	setgaps,        {.i = 0  } },
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

