/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define WindowMask Mod4Mask 
#define AltMask Mod1Mask

#define TAGKEYS(KEY,TAG)												\
	&((Keychord){1, {{WindowMask, KEY}},								view,           {.ui = 1 << TAG} }), \
		&((Keychord){1, {{WindowMask|ControlMask, KEY}},					toggleview,     {.ui = 1 << TAG} }), \
		&((Keychord){1, {{WindowMask|ShiftMask, KEY}},						tag,            {.ui = 1 << TAG} }), \
		&((Keychord){1, {{WindowMask|ControlMask|ShiftMask, KEY}},			toggletag,      {.ui = 1 << TAG} }),

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

/* Application */
static const char *termcmd[]  = {"alacritty", NULL};
static const char *emacs[] = {"emacsclient", "-c", "-a", "\"emacs\"", NULL};
static const char *rofi[] = { "rofi", "-show", "run", NULL};
static const char *browser[] = { "google-chrome-stable", NULL};
static const char *email[] = { "thunderbird", NULL};
static const char *note[] = { "xournalpp", NULL};

/* rofi */

static const char *autorandr[] = {"/home/hain/.scripts/rofi/display", NULL};
static const char *soundcard[] = {"/home/hain/.scripts/rofi/soundcard-choose", NULL};
static const char *search[] = {"/home/hain/.scripts/rofi/rofi-search/search", "search", NULL};
static const char *quickmark[] = {"/home/hain/.scripts/rofi/rofi-search/search", "quickmark", NULL};
static const char *youtube[] = {"/home/hain/.scripts/rofi/rofi-youtube/rofi-youtube", NULL};
static const char *network[] = {"/home/hain/.scripts/rofi/wifi", NULL};
static const char *bluetooth[] = {"/home/hain/.scripts/rofi/rofi-bluetooth/bluetooth", NULL};
static const char *music[] = {"/home/hain/.scripts/rofi/rofi-music/music.sh", NULL};
static const char *wacom[] = {"/home/hain/.scripts/rofi/wacom", NULL};
static const char *logout[] = {"/home/hain/.scripts/rofi/logout", NULL};

/* multimedia  */
static const char *mediaplaypause[] = {"playerctl", "play-pause", NULL};
static const char *mediaprev[] = {"playerctl", "previous", NULL};
static const char *medianext[] = {"playerctl", "next", NULL};
static const char *volumetoggle[] = {"/home/hain/.scripts/system/pavolume.sh", "--togmute", NULL};
static const char *volumedown[] = {"/home/hain/.scripts/system/pavolume.sh", "--down", NULL};
static const char *volumeup[] = {"/home/hain/.scripts/system/pavolume.sh", "--up", NULL};
static const char *brightnessup[] = {"lux", "-a", "1%", NULL};
static const char *brightnessdown[] = {"lux", "-s", "1%", NULL};
static const char *touchpadtoggle[] = {"/home/hain/.scripts/system/touchpad-toggle", NULL};
static const char *printscreencrop[] = {"/home/hain/.scripts/system/print-screen", "-c", NULL};
static const char *printscreenwindow[] = {"/home/hain/.scripts/system/print-screen", "-w", NULL};
static const char *printscreenmonitor[] = {"/home/hain/.scripts/system/print-screen", "-m", NULL};
static const char *printscreenall[] = {"/home/hain/.scripts/system/print-screen", "-w", NULL};


static Keychord *keychords[] = {
    /* modifier      keychord                                                            function                             argument */
    /*Application*/
    &((Keychord){1, {{WindowMask|ShiftMask, XK_Return}},                                 spawn,                          {.v = rofi}}),
    &((Keychord){1, {{WindowMask, XK_Return}},                                           spawn,                          {.v = termcmd}}),
    &((Keychord){1, {{ControlMask|AltMask,XK_e}},                                        spawn,                          {.v = emacs } }),
    &((Keychord){1, {{ControlMask|AltMask,XK_w}},                                        spawn,                          {.v = browser } }),
    &((Keychord){1, {{ControlMask|AltMask,XK_n}},                                        spawn,                          {.v = note } }),
    &((Keychord){1, {{ControlMask|AltMask,XK_m}},                                        spawn,                          {.v = email } }),
    /* Scripts */

    &((Keychord){2, {{WindowMask, XK_p}, {WindowMask, XK_p}},                            spawn,                          {.v = autorandr}}),
    &((Keychord){2, {{WindowMask, XK_p}, {0, XK_p}},                                     spawn,                          {.v = autorandr}}),
    &((Keychord){2, {{WindowMask, XK_p}, {WindowMask, XK_a}},                            spawn,                          {.v = soundcard}}),
    &((Keychord){2, {{WindowMask, XK_p}, {0, XK_a}},                                     spawn,                          {.v = soundcard}}),
    &((Keychord){2, {{WindowMask, XK_o}, {WindowMask, XK_o}},                            spawn,                          {.v = search}}),
    &((Keychord){2, {{WindowMask, XK_o}, {0, XK_o}},                                     spawn,                          {.v = search}}),
    &((Keychord){2, {{WindowMask, XK_o}, {WindowMask, XK_m}},                            spawn,                          {.v = quickmark}}),
    &((Keychord){2, {{WindowMask, XK_o}, {0, XK_m}},                                     spawn,                          {.v = quickmark}}),
    &((Keychord){2, {{WindowMask, XK_o}, {WindowMask, XK_y}},                            spawn,                          {.v = youtube}}),
    &((Keychord){2, {{WindowMask, XK_o}, {0, XK_y}},                                     spawn,                          {.v = youtube}}),
    &((Keychord){2, {{WindowMask, XK_p}, {WindowMask, XK_w}},                            spawn,                          {.v = network}}),
    &((Keychord){2, {{WindowMask, XK_p}, {0, XK_w}},                                     spawn,                          {.v = network}}),
    &((Keychord){2, {{WindowMask, XK_p}, {WindowMask, XK_b}},                            spawn,                          {.v = bluetooth}}),
    &((Keychord){2, {{WindowMask, XK_p}, {0, XK_b}},                                     spawn,                          {.v = bluetooth}}),
    &((Keychord){2, {{WindowMask, XK_p}, {WindowMask, XK_m}},                            spawn,                          {.v = music}}),
    &((Keychord){2, {{WindowMask, XK_p}, {0, XK_m}},                                     spawn,                          {.v = music}}),
    &((Keychord){2, {{WindowMask, XK_p}, {WindowMask, XK_t}},                            spawn,                          {.v = wacom}}),
    &((Keychord){2, {{WindowMask, XK_p}, {0, XK_t}},                                     spawn,                          {.v = wacom}}),
    &((Keychord){2, {{WindowMask, XK_p}, {WindowMask, XK_q}},                            spawn,                          {.v = logout}}),
    &((Keychord){2, {{WindowMask, XK_p}, {0, XK_q}},                                     spawn,                          {.v = logout}}),

    /*Multimedia*/

    &((Keychord){1, {{0,XF86XK_AudioPlay}},                                              spawn,                          {.v = mediaplaypause}}),
    &((Keychord){1, {{WindowMask|ShiftMask, XK_slash}},                                  spawn,                          {.v = mediaplaypause}}),
    &((Keychord){1, {{0,XF86XK_AudioPrev}},                                              spawn,                          {.v = mediaprev}}),
    &((Keychord){1, {{WindowMask|ShiftMask, XK_comma}},                                  spawn,                          {.v = mediaprev}}),
    &((Keychord){1, {{0,XF86XK_AudioNext}},                                              spawn,                          {.v = medianext}}),
    &((Keychord){1, {{WindowMask|ShiftMask, XK_period}},                                 spawn,                          {.v = medianext}}),
    &((Keychord){1, {{0,XF86XK_AudioMute}},                                              spawn,                          {.v = volumetoggle}}),
    &((Keychord){1, {{0,XF86XK_AudioRaiseVolume}},                                       spawn,                          {.v = volumeup}}),
    &((Keychord){1, {{0,XF86XK_AudioLowerVolume}},                                       spawn,                          {.v = volumedown}}),
    &((Keychord){1, {{0,XF86XK_MonBrightnessUp}},                                        spawn,                          {.v = brightnessup}}),
    &((Keychord){1, {{0,XF86XK_MonBrightnessDown}},                                      spawn,                          {.v = brightnessdown}}),
    &((Keychord){1, {{0,XF86XK_TouchpadToggle}},                                         spawn,                          {.v = touchpadtoggle}}),
    &((Keychord){1, {{0,XK_Print}},                                                      spawn,                          {.v = printscreencrop}}),
    &((Keychord){1, {{WindowMask,XK_Print}},                                             spawn,                          {.v = printscreenwindow}}),
    &((Keychord){1, {{ControlMask,XK_Print}},                                            spawn,                          {.v = printscreenmonitor}}),
    &((Keychord){1, {{WindowMask|ShiftMask,XK_Print}},                                   spawn,                          {.v = printscreenall}}),
 
    &((Keychord){1, {{WindowMask|ShiftMask,XK_r}},                                       restart,        {0}}),

    /*window*/
    TAGKEYS(XK_1,                                                       0)
    TAGKEYS(XK_2,                                                       1)
    TAGKEYS(XK_3,                                                       2)
    TAGKEYS(XK_4,                                                       3)
    TAGKEYS(XK_5,                                                       4)
    TAGKEYS(XK_6,                                                       5)
    TAGKEYS(XK_7,                                                       6)
    TAGKEYS(XK_8,                                                       7)
    TAGKEYS(XK_9,                                                       8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         WindowMask,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         WindowMask,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         WindowMask,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            WindowMask,         Button1,        tag,            {0} },
	{ ClkTagBar,            WindowMask,         Button3,        toggletag,      {0} },
};

