static void
fibonacci(Monitor *m, int s)
{
	unsigned int i, n, oe = enablegaps, ie = enablegaps;
	int nx, ny, nw, nh;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;
	if (n == 1) {
		c = nexttiled(m->clients);
		resize(c, m->wx + m->gappov*oe, m->wy + m->gappoh*oe, m->ww - 2 * c->bw - 2*m->gappov*oe, m->wh - 2 * c->bw - 2*m->gappoh*oe, 0);
		return;
	}

	nx = m->wx + m->gappov*oe;
	ny = m->gappoh*oe;
	nw = m->ww - 2*m->gappov*oe;
	nh = m->wh - 2*m->gappoh*oe;

	for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next)) {
		if ((i % 2 && nh / 2 > 2*c->bw)
		   || (!(i % 2) && nw / 2 > 2*c->bw)) {
			if (i < n - 1) {
				if (i % 2)
					nh = (nh - m->gappiv*ie) / 2;
				else
					nw = (nw - m->gappih*ie) / 2;

				if ((i % 4) == 2 && !s)
					nx += nw + m->gappiv*ie;
				else if ((i % 4) == 3 && !s)
					ny += nh + m->gappih*ie;
			}
			if ((i % 4) == 0) {
				if (s)
					ny += nh + m->gappih*ie;
				else
					ny -= nh + m->gappiv*ie;
			}
			else if ((i % 4) == 1)
				nx += nw + m->gappiv*ie;
			else if ((i % 4) == 2)
				ny += nh + m->gappih*ie;
			else if ((i % 4) == 3) {
				if (s)
					nx += nw + m->gappiv*ie;
				else
					nx -= nw + m->gappiv*ie;
			}
			if (i == 0)	{
				if (n != 1)
					nw = (m->ww - 2*m->gappov*oe - m->gappiv*ie) * m->mfact;
				ny = m->wy + m->gappoh*oe;
			}
			else if (i == 1)
				nw = m->ww - nw - m->gappiv*ie - 2*m->gappov*oe;
			i++;
		}

		resize(c, nx, ny, nw - (2*c->bw), nh - (2*c->bw), False);
	}
}

void
dwindle(Monitor *mon) {
	fibonacci(mon, 1);
}

void
spiral(Monitor *mon) {
	fibonacci(mon, 0);
}
