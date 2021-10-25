src = cwm.c handlers.c util.c draw.c
cwm: $(src)
	$(CC) $(src) -lX11 -g -o cwm

clean:
	rm cwm