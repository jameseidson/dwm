/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 1;  /* border pixel of windows */
static const int swallowfloating         = 0;  /* 1 means swallow floating windows by default */
static const unsigned int snap           = 32; /* snap pixel */
static const unsigned int systraypinning = 0;  /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;  /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;  /* systray spacing */
static const int systraypinningfailfirst = 1;  /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;  /* 0 means no systray */
static const int showbar                 = 1;  /* 0 means no bar */
static const int topbar                  = 1;  /* 0 means bottom bar */
static const char *fonts[]               = { "JetBrainsMono Nerd Font:size=11" };

/* colors */
static const char dark0_hard[]      = "#1D2021";
static const char gray_245[]        = "#928374";
static const char light0_hard[]     = "#F9F5D7";
static const char light1[]          = "#EBDBB2";
static const char faded_yellow[]    = "#B57614";
static const char forest_green[]    = "#302F17";
static const char *colors[][3]      = {
	/*                  text           background      border                         */
	[SchemeNorm]      = { light1,      dark0_hard,    forest_green  }, // unfocused window
	[SchemeSel]       = { light1,      dark0_hard,    gray_245      }, // focused window 
	[SchemeStatus]    = { light1,      dark0_hard,    "#000000"     }, // Statusbar right
	[SchemeTagsSel]   = { light0_hard, faded_yellow,  "#000000"     }, // Tagbar left selected
	[SchemeTagsNorm]  = { light1,      dark0_hard,    "#000000"     }, // Tagbar left unselected
	[SchemeInfoSel]   = { light0_hard, forest_green,  "#000000"     }, // infobar middle selected
	[SchemeInfoNorm]  = { light1,      dark0_hard,    "#000000"     }, // infobar middle unselected
};

/* tagging */
static const char *tags[] = { "1 term", "2 code", "3 web", "4", "5", "6", "7", "8", "9 misc" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                instance  title     tags mask switchtotag  isfloating  isterminal  noswallow  monitor */
	{ "Alacritty",          NULL,     NULL,     1,        1,           0,          1,          0,         -1 },
	// { NULL,                 NULL,     "helix",  1 << 1,   1,           0,          0,          0,         -1 },
	{ "firefox",            NULL,     NULL,     1 << 2,   1,           0,          0,          0,         -1 },
	{ "Mailspring",         NULL,     NULL,     1 << 9,   1,           0,          0,          0,         -1 },
	{ "Bitwarden",          NULL,     NULL,     0,        0,           1,          0,          0,         -1 },
	{ "Blueman-manager",    NULL,     NULL,     0,        0,           1,          0,          0,         -1 },
	{ "Qemu-system-x86_64", NULL,     NULL,     0,        0,           0,          0,          1,         -1 }
};

/* layout(s) */
static const float mfact        = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;    /* 1 will force focus on the fullscreen window */

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
// static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *termcmd[]  = { "alacritty", NULL };
static const char *dmenucmd[] = { "rofi", "-modi", "drun", "-show", "drun", NULL };
static const char *swapcmd[]  = { "rofi", "-theme-str", "window {width: 30%;}", "-show", "window", NULL };

static const char *web[]    = { "firefox", NULL }; 
// static const char *editor[] = { "alacritty", "--title", "helix", "-e", "hx", NULL };
static const char *mail[]   = { "mailspring", NULL };

static const char *powermenu[] = { "/home/james/config/scripts/powermenu", NULL};
static const char *inc_vol[]   = {"pamixer", "--increase", "1", NULL};
static const char *dec_vol[]   = {"pamixer", "--decrease", "1", NULL};

static Key keys[] = {
	/* modifier                     key              function        argument */
	{ MODKEY,                       XK_Return,       spawn,          {.v = termcmd} },
	{ MODKEY,                       XK_d,            spawn,          {.v = dmenucmd} },
	{ MODKEY,                       XK_w,            spawn,          {.v = web} },
	// { MODKEY,                       XK_c,            spawn,          {.v = editor} },
	{ MODKEY,                       XK_F1,           spawn,          {.v = mail} },
	{ MODKEY,                       XK_b,            togglebar,      {0} },
	{ MODKEY,                       XK_l,            focusstack,     {.i = +1} },
	{ MODKEY,                       XK_h,            focusstack,     {.i = -1} },
	{ MODKEY|ShiftMask,             XK_equal,        incnmaster,     {.i = +1} },
	{ MODKEY|ShiftMask,             XK_minus,        incnmaster,     {.i = -1} },
	{ MODKEY,                       XK_equal,        spawn,          {.v = inc_vol} },
	{ MODKEY,                       XK_minus,        spawn,          {.v = dec_vol} },
	{ MODKEY|ShiftMask,             XK_Return,       zoom,           {0} },
	{ MODKEY,                       XK_Tab,          view,           {0} },
 	{ MODKEY,                       XK_grave,        spawn,          {.v = swapcmd} },
	{ MODKEY,                       XK_q,            killclient,     {0} },
	{ MODKEY,                       XK_t,            setlayout,      {.v = &layouts[0]} }, // tiled
	{ MODKEY,                       XK_f,            setlayout,      {.v = &layouts[1]} }, // floating
	{ MODKEY,                       XK_m,            setlayout,      {.v = &layouts[2]} }, // fullscreen ('monacle')
	{ MODKEY,                       XK_space,        togglefloating, {0} },
	{ MODKEY,                       XK_0,            view,           {.ui = ~0} },
	{ MODKEY|ShiftMask,             XK_0,            tag,            {.ui = ~0} },
	{ MODKEY,                       XK_bracketleft,  focusmon,       {.i = -1} },
	{ MODKEY,                       XK_bracketright, focusmon,       {.i = +1} },
	{ MODKEY|ShiftMask,             XK_bracketleft,  tagmon,         {.i = -1} },
	{ MODKEY|ShiftMask,             XK_bracketright, tagmon,         {.i = +1} },
	TAGKEYS(                        XK_1,                             0)
	TAGKEYS(                        XK_2,                             1)
	TAGKEYS(                        XK_3,                             2)
	TAGKEYS(                        XK_4,                             3)
	TAGKEYS(                        XK_5,                             4)
	TAGKEYS(                        XK_6,                             5)
	TAGKEYS(                        XK_7,                             6)
	TAGKEYS(                        XK_8,                             7)
	TAGKEYS(                        XK_9,                             8)
	{ MODKEY|ShiftMask,             XK_q,            spawn,          {.v = powermenu} },
	{ MODKEY|ShiftMask,             XK_x,            quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
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
