/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int snap      = 32;       /* snap pixel */

/* Tag previews */
static const int scalepreview       = 4;        /* preview scaling (display w and h / scalepreview) */
static const int previewbar         = 1;        /* show the bar in the preview window */

/* Vanitygaps */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */

/* Systray */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 4;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/

static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const char *fonts[]          = { "Mononoki Nerd Font:size=14" };
static const char dmenufont[]       = "Mononoki Nerd Font:size=14";
static const char col_gray1[]       = "#8FBCBB";
static const char col_gray2[]       = "#2e3440";
static const char col_gray3[]       = "#2e3440";
static const char col_gray4[]       = "#8FBCBB";
static const char col_cyan[]        = "#2e3440";
static const char col_orange[]      = "#ed7a0e";
static const char col_teal[]        = "#71b7d1";
static const char col_black[]       = "#000000";
static const char col_yellow[]      = "#ffee00";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_black },
	[SchemeSel]  = { col_gray4, col_cyan,  col_yellow  },
	[SchemeStatus]  = { col_gray3, col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_gray4, col_cyan,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm]  = { col_gray3, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
	[SchemeInfoSel]  = { col_gray4, col_cyan,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm]  = { col_gray3, col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "󰣇", "󰶞", "󰚯", "", "", "󰛏", "󰑋", "󰙯" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
    /* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         0,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           0,         0,          0,          -1,        -1 },
	{ "kitty",   NULL,     NULL,           0,         0,          1,           0,        -1 },
    { "Spotify", NULL,     NULL,           1 << 4,    0,          0,           0,        -1 },
    { "discord", NULL,     NULL,           1 << 7,    0,          0,           0,        -1 },
    { "org.mozilla.Thunderbird", NULL, NULL, 1 << 5,  0,          0,           0,        -1 },
    { "Signal", NULL,      NULL,           1 << 7,    0,          0,           0,        -1 },
    { "steam",   NULL,     NULL,           1 << 3,    0,          0,           0,        -1 },
    { "obs",     NULL,     NULL,           1 << 6,    0,          0,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* for popup windows */
    { "gnome-calculator",  NULL, NULL,     0,         1,          0,           0,        -1 },
    { "unityhub", NULL,    NULL,           1 << 2,    0,          0,           0,        -1 },
    { "tidal-hifi", NULL,  NULL,           1 << 4,    0,          0,           0,        -1 },

};

/* Vanitygaps definitions */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
    { "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define SUPERKEY Mod4Mask

/* Knob keys */
#define XF86XK_AudioMute        0x1008ff12   /* Mute sound from the system */
#define XF86XK_AudioRaiseVolume 0x1008ff13   /* Raise system audio volume */
#define XF86XK_AudioLowerVolume 0x1008ff11   /* Lower system audio volume */

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      previewtag,     {.ui = TAG } },     \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"
#include "movestack.c"
#include <stdlib.h>

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show-icons", "-show", "drun", NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *firefoxcmd[] = { "firefox", NULL };
static const char *up_vol[] = { "/bin/sh", "-c", "$HOME/.local/bin/volume.sh up", NULL };
static const char *down_vol[] = { "/bin/sh", "-c", "$HOME/.local/bin/volume.sh down", NULL };
static const char *mute_vol[] = { "/bin/sh", "-c", "$HOME/.local/bin/volume.sh mute", NULL };
static const char *colorpickercmd[] = { "/bin/sh", "-c", "$HOME/.local/bin/colorpicker.sh", NULL };
static const char *prntscrncmd_copyarea[] = { "/bin/sh", "-c", "$HOME/.local/bin/screenshot -copy_area", NULL };
static const char *prntscrncmd_copyfull[] = { "/bin/sh", "-c", "$HOME/.local/bin/screenshot -copy_full", NULL };
static const char *prntscrncmd_area[] = { "/bin/sh", "-c", "$HOME/.local/bin/screenshot -area", NULL };
static const char *prntscrncmd_full[] = { "/bin/sh", "-c", "$HOME/.local/bin/screenshot -full", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
    { MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY|ControlMask,           XK_c,      killclient,     {.ui = 1} },  // kill unselect
    { MODKEY|ShiftMask|ControlMask, XK_c,      killclient,     {.ui = 2} },  // killall
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_v,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_b,      setlayout,      {.v = &layouts[5]} },
    { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[7]} },
    { MODKEY,                       XK_c,      setlayout,      {.v = &layouts[11]} },
    { MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODKEY|ControlMask,           XK_space,  focusmaster,    {0} },
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
    { MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} },
    { MODKEY,                       XK_s,      togglesticky,   {0} },
    { 0,                            XK_Print,  spawn,         {.v = prntscrncmd_copyarea } },
    { 0,                            XF86XK_AudioMute,  spawn, {.v = mute_vol } },
    { 0,                            XF86XK_AudioLowerVolume, spawn, {.v = down_vol } },
    { 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = up_vol } },
    { MODKEY,                       XK_w,      spawn,         {.v = firefoxcmd } },
    { MODKEY,                       XK_a,      spawn,         SHCMD("echo toggle > /tmp/ai-assistant.pipe") },
    { MODKEY | ShiftMask,           XK_l,      spawn,         SHCMD("slock") },
    { MODKEY,                       XK_Insert, spawn,         {.v = colorpickercmd } },
    { 0,                            XK_F12,    spawn,         {.v = prntscrncmd_copyfull } },
    { MODKEY,                       XK_Print,  spawn,         {.v = prntscrncmd_area } },
    { MODKEY,                       XK_F12,    spawn,         {.v = prntscrncmd_full } },
    { MODKEY,                       XK_F11,    spawn,         SHCMD("echo stop > /tmp/ai-assistant.pipe") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	
    /* Systray patchin mukaan kaks ylint rivii kuuluis poistaa? */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
