/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 10;       /* horizontal padding for statusbar */
static const int vertpadbar         = 10;       /* vertical padding for statusbar */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const char *fonts[]          = { "Misc Tamsyn:size=12" };

/* gruvbox colors */
static const char dark0_hard[]      = "#1D2021";
// static const char dark0[]           = "#282828";
// static const char dark0_soft[]      = "#32302F";
// static const char dark1[]           = "#3c3836";
// static const char dark2[]           = "#504945";
// static const char dark3[]           = "#665C54";
// static const char dark4[]           = "#7C6F64";

static const char gray_245[]        = "#928374";
// static const char gray_244[]        = "#928374";

static const char light0_hard[]     = "#F9F5D7";
// static const char light0[]          = "#FBF1C7";
// static const char light0_soft[]     = "#F2E5BC";
static const char light1[]          = "#EBDBB2";
// static const char light2[]          = "#D5C4A1";
// static const char light3[]          = "#BDAE93";
// static const char light4[]          = "#A89984";

// static const char bright_red[]      = "#FB4934";
// static const char bright_green[]    = "#B8BB26";
// static const char bright_yellow[]   = "#FABD2F";
// static const char bright_blue[]     = "#83A598";
// static const char bright_purple[]   = "#D3869B";
// static const char bright_aqua[]     = "#8EC07C";
// static const char bright_orange[]   = "#FE8019";

// static const char neutral_red[]     = "#CC241D";
// static const char neutral_green[]   = "#98971A";
// static const char neutral_yellow[]  = "#D79921";
// static const char neutral_blue[]    = "#458588";
// static const char neutral_purple[]  = "#B16286";
// static const char neutral_aqua[]    = "#689D6A";
// static const char neutral_orange[]  = "#D65D0E";

// static const char faded_red[]       = "#9D0006";
// static const char faded_green[]     = "#79740E";
static const char faded_yellow[]    = "#B57614";
//static const char faded_blue[]      = "#076678";
//static const char faded_purple[]    = "#8F3F71";
//static const char faded_aqua[]      = "#427B58";
// static const char faded_orange[]    = "#AF3A03";

/* custom colors */
static const char forest_green[]    = "#302F17";

static const char *colors[][3]      = {
	/*                  text           background      border                         */
	[SchemeNorm]      = { light1,      dark0_hard,    dark0_hard  }, // unfocused window
	[SchemeSel]       = { light1,      dark0_hard,    gray_245    }, // focused window 
	[SchemeStatus]    = { light1,      dark0_hard,    "#000000"   }, // Statusbar right
	[SchemeTagsSel]   = { light0_hard, faded_yellow,  "#000000"   }, // Tagbar left selected
	[SchemeTagsNorm]  = { light1,      dark0_hard,    "#000000"   }, // Tagbar left unselected
	[SchemeInfoSel]   = { light0_hard, forest_green,  "#000000"   }, // infobar middle selected
	[SchemeInfoNorm]  = { light1,      dark0_hard,    "#000000"   }, // infobar middle unselected
};

/* tagging */
static const char *tags[] = { "", "", "", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class           instance    title       tags mask     switchtotag   isfloating   monitor */
	{ "Alacritty",     NULL,       NULL,       1,            1,            0,           -1 },
	{ "Code",          NULL,       NULL,       1 << 1,       1,            0,           -1 },
	{ "firefox",       NULL,       NULL,       1 << 2,       1,            0,           -1 }
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "=|=",      tile },    /* first entry is default */
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
static const char *termcmd[]   = { "alacritty", NULL };
static const char *dmenucmd[]  = { "rofi", "-modi", "drun", "-show", "drun", NULL };
static const char *swapcmd[]   = { "rofi", "-theme-str", "window {width: 30%;}", "-show", "window", NULL };
static const char *browsecmd[] = { "firefox", NULL }; 
static const char *editcmd[]   = { "code", NULL };

static Key keys[] = {
	/* modifier                     key              function        argument */
	{ MODKEY,                       XK_Return,       spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_d,            spawn,          {.v = dmenucmd} },
	{ MODKEY,                       XK_w,            spawn,          {.v = browsecmd} },
	{ MODKEY,                       XK_c,            spawn,          {.v = editcmd} },
	{ MODKEY,                       XK_b,            togglebar,      {0} },
	{ MODKEY,                       XK_l,            focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_h,            focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_equal,        incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_minus,        incnmaster,     {.i = -1 } },
 // { MODKEY,                       XK_h,            setmfact,       {.f = -0.05} },
 // { MODKEY,                       XK_l,            setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,       zoom,           {0} },
	{ MODKEY,                       XK_Tab,          view,           {0} },
 	{ MODKEY|ShiftMask,             XK_Tab,          spawn,          {.v = swapcmd} },
	{ MODKEY,                       XK_q,            killclient,     {0} },
	{ MODKEY,                       XK_t,            setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,            setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,            setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,        setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,        togglefloating, {0} },
	{ MODKEY,                       XK_0,            view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,            tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_bracketleft,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_bracketright, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_bracketleft,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_bracketright, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                             0)
	TAGKEYS(                        XK_2,                             1)
	TAGKEYS(                        XK_3,                             2)
	TAGKEYS(                        XK_4,                             3)
	TAGKEYS(                        XK_5,                             4)
	TAGKEYS(                        XK_6,                             5)
	TAGKEYS(                        XK_7,                             6)
	TAGKEYS(                        XK_8,                             7)
	TAGKEYS(                        XK_9,                             8)
	{ MODKEY|ShiftMask,             XK_x,            quit,           {0} },
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

