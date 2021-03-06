/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h> // needed for volup and voldown

/* appearance */
static const char *fonts[] = {
	"monospace:size=7.5:antialias=true"
};
static const char dmenufont[]       = "monospace:size=7.5:antialias=true";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005500";
static const char selbgcolor[]      = "#000000";
static const char selfgcolor[]      = "#eeeeee";
static const char listbordercolor[]  = "#001111";
static const char listbgcolor[]      = "#001111";
static const char listfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gapheight = 4;	/* vertical gap between pixels of windows */
static const unsigned int gapwidth  = 4;	/* horizontal gap between pixels of windows */

static const unsigned int wgapheight = 0;	/* vertical gap between pixeels of windows and edge of screen */
static const unsigned int wgapwidth  = 0;	/* horizontal gap between pixels of windows ^^^*/

static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const unsigned int listitemlen = 0;	/* length in pixels of list item max len. 0 means no max */
static const int listhidesel = 1;		/* 0 means show the selected in list */
static const int listhidecount = 0;		/* hide the list if there are equal or fewer than items in it */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
//	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
//	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Xmessage", NULL,	  "xmessage", 0,	    1,		 -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-b", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvtc", NULL };
static const char *voldowncmd[]  = { "volumedown", NULL };
static const char *volupcmd[]  = { "volumeup", NULL };
static const char *dwmcatchercmd[]  = { "dwmcatcher", NULL };
static const char *bgcmd[]  = { "oncething.sh", NULL };
static const char *lockcmd[]  = { "robolock", "-a", "/home/roboman2444/robolock/samplealert.sh", NULL};
static const char *screenupcmd[]  = { "lighterfluid", "double", NULL};
static const char *screendowncmd[]  = { "lighterfluid", "half", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_l,      spawn,          {.v = lockcmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
//	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
//	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_u,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = -1 } },
//	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
//	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_k,      incnmaster,     {.i = -1 } },
//	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
//	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_y,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_y,	setgap,       {.i = +1} },
	{ MODKEY|ShiftMask,             XK_h,	setgap,       {.i = -1} },
	{ MODKEY|ShiftMask,             XK_u,	setwgap,       {.i = +1} },
	{ MODKEY|ShiftMask,             XK_j,	setwgap,       {.i = -1} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_Left,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_Right, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Right, tagmon,         {.i = +1 } },
//	{ MODKEY|ShiftMask,             XK_Left,  tagfocusmon,     {.i = -1 } },
//	{ MODKEY|ShiftMask,             XK_Right, tagfocusmon,     {.i = +1 } },
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
	{ MODKEY|ShiftMask,             XK_r,      spawn,          {.v = dwmcatchercmd} },
	{ MODKEY|ShiftMask,             XK_b,     spawn,      	   {.v = bgcmd} },
	{ 0,				XF86XK_AudioLowerVolume,	spawn,	   {.v = voldowncmd} },
	{ 0,				XF86XK_AudioRaiseVolume,	spawn,	   {.v = volupcmd} },
	{ 0,				XF86XK_MonBrightnessUp,		spawn,	   {.v = screenupcmd} },
	{ 0,				XF86XK_MonBrightnessDown,	spawn,	   {.v = screendowncmd} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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
