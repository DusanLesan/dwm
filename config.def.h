/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "alacritty"

/* appearance */
static const unsigned int borderpx       = 2;   /* border pixel of windows */
static const unsigned int snap           = 15;  /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;   /* 0 means no systray */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
static const char *fonts[]               = { "monospace:size=10" };
static const char dmenufont[]            = "monospace:size=10";
static const char col_gray1[]            = "#181818";
static const char col_gray2[]            = "#444444";
static const char col_gray3[]            = "#bbbbbb";
static const char col_gray4[]            = "#eeeeee";
static const char col_cyan[]             = "#005577";
static const char col_red[]              = "#A54242";
static const char *colors[][3]           = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan , col_red },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance   title  tags mask  isfloating   monitor  float x,y,w,h  floatborderpx*/
	{ "code-oss",    NULL,   NULL,   1 << 1,   0,           1 },
	{ "SmartGit",    NULL,   NULL,   1 << 2,   0,           1 },
	{ "Insomnia",    NULL,   NULL,   1 << 3,   0,           1 },
	{ "RALE",        NULL,   NULL,   1 << 4,   0,           1 },
	{ "Skype",       NULL,   NULL,   1 << 0,   0,           0 },
	{ "Slack",       NULL,   NULL,   1 << 0,   0,           0 },
	{ "Mattermost",  NULL,   NULL,   1 << 0,   0,           0 },
	{ "mpv",         NULL,   NULL,   0 << 0,   0,           1 },
	{ "Steam",       NULL,   NULL,   0 << 0,   0,           0 },
	{ "floating",    NULL,   NULL,   -1,       1,           -1,  1414,19,500,500,  2 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,              KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier            key            function         argument */
	{ MODKEY,              XK_d,          spawn,           {.v = dmenucmd } },
	{ MODKEY,              XK_Return,     spawn,           {.v = termcmd } },
	{ MODKEY,              XK_t,          spawn,           {.v = termcmd } },
	{ MODKEY,              XK_f,          spawn,           SHCMD("_START_LFCD=1 " TERMINAL) },
	{ MODKEY,              XK_F1,         spawn,           SHCMD("$BROWSER") },
	{ MODKEY|ControlMask,  XK_F1,         spawn,           SHCMD("$BROWSER --incognito") },
	{ MODKEY|ShiftMask,    XK_F1,         spawn,           SHCMD("$BROWSER --tor") },
	{ MODKEY|Mod1Mask,     XK_F1,         spawn,           SHCMD("bookmarks") },
	{ MODKEY,              XK_F2,         spawn,           SHCMD("code") },
	{ MODKEY,              XK_F3,         spawn,           SHCMD("smartgit") },
	{ MODKEY,              XK_F4,         spawn,           SHCMD("insomnia") },
	{ MODKEY,              XK_F5,         spawn,           SHCMD("roku") },
	{ MODKEY,              XK_F8,         spawn,           SHCMD("comms") },
	{ MODKEY|ShiftMask,    XK_F8,         spawn,           SHCMD("comms -q") },
	{ MODKEY,              XK_F12,        spawn,           SHCMD("dmenucalc") },
	{ MODKEY,              XK_b,          togglebar,       {0} },
	{ MODKEY,              XK_space,      zoom,            {0} },
	{ MODKEY|Mod1Mask,     XK_Tab,        focusmon,        {.i = -1 } },
	{ MODKEY,              XK_Tab,        focusmon,        {.i = +1 } },
	{ MODKEY,              XK_Left,       focusstack,      {.i = -1 } },
	{ MODKEY,              XK_Right,      focusstack,      {.i = +1 } },
	{ MODKEY,              XK_Up,         pushup,         {0} },
	{ MODKEY,              XK_Down,       pushdown,       {0} },
	{ MODKEY|Mod1Mask,     XK_Left,       tagmon,          {.i = -1 } },
	{ MODKEY|Mod1Mask,     XK_Right,      tagmon,          {.i = +1 } },
	{ MODKEY|Mod1Mask,     XK_Page_Up,    incnmaster,      {.i = +1 } },
	{ MODKEY|Mod1Mask,     XK_Page_Down,  incnmaster,      {.i = -1 } },
	{ MODKEY|ControlMask,  XK_Page_Up,    setcfact,        {.f = +0.25} },
	{ MODKEY|ControlMask,  XK_Page_Down,  setcfact,        {.f = -0.25} },
	{ MODKEY|ControlMask,  XK_End,        setcfact,        {.f = 0.00} },
	{ MODKEY,              XK_h,          setmfact,        {.f = -0.05} },
	{ MODKEY,              XK_l,          setmfact,        {.f = +0.05} },
	{ MODKEY,              XK_q,          killclient,      {0} },
	{ MODKEY|Mod1Mask,     XK_t,          setlayout,       {.v = &layouts[0]} },
	{ MODKEY|Mod1Mask,     XK_f,          setlayout,       {.v = &layouts[1]} },
	{ MODKEY|Mod1Mask,     XK_m,          setlayout,       {.v = &layouts[2]} },
	{ MODKEY|Mod1Mask,     XK_u,          setlayout,       {.v = &layouts[3]} },
	{ MODKEY|Mod1Mask,     XK_space,      togglefloating,  {0} },
	{ MODKEY,              XK_0,          view,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,    XK_0,          tag,             {.ui = ~0 } },
	{ MODKEY|ControlMask,  XK_p,          spawn,           SHCMD("display_switch") },
	{ MODKEY|ShiftMask,    XK_p,          spawn,           SHCMD("displayselect") },
	{ 0,                   XK_Print,      spawn,           SHCMD("maim -i `xdotool getactivewindow` ~/hdd_1/Pictures/screenshot/pic-window-$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,           XK_Print,      spawn,           SHCMD("maimpick") },
	{ MODKEY,              XK_equal,      spawn,           SHCMD("pamixer --allow-boost -i 5; kill -39 $(pidof dwmblocks)") },
	{ MODKEY,              XK_minus,      spawn,           SHCMD("pamixer --allow-boost -d 5; kill -39 $(pidof dwmblocks)") },
	{ MODKEY,              XK_F9,         spawn,           SHCMD("dmenumount") },
	{ MODKEY,              XK_F10,        spawn,           SHCMD("dmenuumount") },
	{ MODKEY|ShiftMask,    XK_l,          spawn,           SHCMD("slock || kill -9 -1") },
	{ 0,                   XK_Pause,      spawn,           SHCMD("dunstctl close") },
	{ MODKEY,              XK_Pause,      spawn,           SHCMD("dunstctl set-paused toggle") },
	{ ShiftMask,           XK_Pause,      spawn,           SHCMD("dunstctl history-pop") },
	{ ControlMask,         XK_Pause,      spawn,           SHCMD("dunst_config") },
	{ MODKEY|ShiftMask,    XK_q,          spawn,           SHCMD("sysact") },
	TAGKEYS(               XK_2,          1)
	TAGKEYS(               XK_3,          2)
	TAGKEYS(               XK_1,          0)
	TAGKEYS(               XK_4,          3)
	TAGKEYS(               XK_5,          4)
	TAGKEYS(               XK_6,          5)
	TAGKEYS(               XK_7,          6)
	TAGKEYS(               XK_8,          7)
	TAGKEYS(               XK_9,          8)
	{ 0,                   XF86XK_AudioPlay,         spawn,  SHCMD("music") },
	{ 0,                   XF86XK_AudioMute,         spawn,  SHCMD("pamixer -t; kill -39 $(pidof dwmblocks)") },
	{ 0,                   XF86XK_AudioRaiseVolume,  spawn,  SHCMD("pamixer --allow-boost -i 3; kill -39 $(pidof dwmblocks)") },
	{ 0,                   XF86XK_AudioLowerVolume,  spawn,  SHCMD("pamixer --allow-boost -d 3; kill -39 $(pidof dwmblocks)") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click           event mask   button     function          argument */
	{ ClkLtSymbol,     0,           Button1,   setlayout,        {0} },
	{ ClkLtSymbol,     0,           Button3,   setlayout,        {.v = &layouts[2]} },
	{ ClkWinTitle,     0,           Button2,   zoom,             {0} },
	{ ClkStatusText,   0,           Button1,   sigstatusbar,     {.i = 1} },
	{ ClkStatusText,   0,           Button2,   sigstatusbar,     {.i = 2} },
	{ ClkStatusText,   0,           Button3,   sigstatusbar,     {.i = 3} },
	{ ClkStatusText,   0,           Button4,   sigstatusbar,     {.i = 4} },
	{ ClkStatusText,   0,           Button5,   sigstatusbar,     {.i = 5} },
	{ ClkStatusText,   ShiftMask,   Button1,   sigstatusbar,     {.i = 6} },
	{ ClkClientWin,    MODKEY,      Button1,   movemouse,        {0} },
	{ ClkClientWin,    MODKEY,      Button2,   togglefloating,   {0} },
	{ ClkClientWin,    MODKEY,      Button3,   resizemouse,      {0} },
	{ ClkTagBar,       0,           Button1,   view,             {0} },
	{ ClkTagBar,       0,           Button3,   toggleview,       {0} },
	{ ClkTagBar,       MODKEY,      Button1,   tag,              {0} },
	{ ClkTagBar,       MODKEY,      Button3,   toggletag,        {0} },
};
