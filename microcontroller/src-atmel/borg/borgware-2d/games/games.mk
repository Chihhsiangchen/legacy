
ifeq ($(GAME_TETRIS_CORE),y)
  SUBDIRS += games/tetris
endif

ifeq ($(GAME_SPACE_INVADERS),y)
  SUBDIRS += games/space_invaders
endif

ifeq ($(GAME_SNAKE),y)
  SUBDIRS += games/snake
endif

ifeq ($(ANIMATION_SNAKE),y)
  ifneq ($(GAME_SNAKE),y)
    SUBDIRS += games/snake
  endif
endif

ifeq ($(GAME_BREAKOUT),y)
  SUBDIRS += games/breakout
endif
