BINNVIF_CC = $(CFLAGS)
BINNVIF_LD = $(LDFLAGS) -lnvif -lncurses -lmenu -lform -L$(lib)

srcs = $(wildcard $(bin)/*.c)
outp = $(srcs:.c=)

$(outp): %: %.c $(lib)/libnvif.so
	@echo -e "  CCLD     $@"
	@$(CC) $(BINNVIF_CC) $(BINNVIF_LD) -MMD -MP -o $@ $<

deps += $(srcs:.c=.d)
bins += $(outp)
