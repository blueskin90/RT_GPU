#ifndef CUT
	#define CUT

vec2 lameCut(vec2 form, vec2 cutter, vec3 formNX, vec3 formNY, out vec3 nx, out vec3 ny)
{
	vec2 res = form;
	nx = formNX;
	ny = formNY;

	if (isinf(form.x) && isinf(form.x))
		return vec2(INFINITY);

	if (form.x > 0.0 && form.y > 0.0 && cutter.x < 0.0 && cutter.y < 0.0)
		return res;

	// Both outside
	if (cutter.y > 0.0 && form.y > 0.0)
	{
		if (cutter.x < form.x && cutter.y > form.y)
		{
			res.x = INFINITY;
		}
		else if(cutter.x < form.x && cutter.y > form.x)
		{
			res.x = form.y;
			nx = formNY;
		}

		if(cutter.y > form.y && cutter.x < form.y)
			res.y = INFINITY;
		return res;
	}

	if (form.x > 0.0 && form.y < 0.0 && cutter.x < 0.0)
	{
		if(cutter.y < form.y)
			res.y = INFINITY;
		return res;
	}

	// Both inside
	if (cutter.y < 0.0 && cutter.x > 0.0 && form.y < 0.0 && form.x > 0.0)
	{
		if (cutter.x > form.x)
			res.x = INFINITY;
		if(cutter.y < form.y)
			res.y = INFINITY;
		return res;
	}

	// Inside cutter
	if (cutter.y < 0.0 && form.y > 0.0)
	{
		res.y = INFINITY;
		if (cutter.x > form.y)
		{
			res.x = INFINITY;
		}
		else if (cutter.x > form.x)
		{
			res.x = form.y;
			nx = -formNY;
		}
		return res;
	}

	// Inside form
	if (form.x > 0.0 && form.y < 0.0 && cutter.y > 0.0)
	{
		if (cutter.x < form.x && cutter.y > form.x && !isinf(cutter.x))
			res.x = INFINITY;
	}

	return res;
}

vec2 cut(vec2 form, vec2 cutter, vec3 formNX, vec3 formNY, vec3 cutterNX, vec3 cutterNY, out vec3 nx, out vec3 ny)
{
	vec2 res = form;
	nx = formNX;
	ny = formNY;

	// if (isinf(form.x))
	// 	return vec2(INFINITY);

	if (form.x > 0.0 && form.y > 0.0 && cutter.x < 0.0 && cutter.y < 0.0)
		return res;

	// Both outside
	if (cutter.y > 0.0 && form.y > 0.0)
	{
		if (cutter.x < form.x && cutter.y > form.x)
		{
			res.x = (cutter.y > form.y) ? INFINITY : cutter.y;
			nx = cutterNY;
		}
		if (cutter.x < form.y && cutter.x > form.x)
		{
			res.y = cutter.x;
			ny = cutterNX;
		}
		return res;
	}

	if (form.x > 0.0 && form.y < 0.0 && cutter.x < 0.0)
	{
		if (form.y < cutter.x)
		{
			res.x = form.x;
			nx = formNX;

			res.y = cutter.x;
			ny = cutterNX;
			// res.y = 1;
			return res;
		}
	}

	// Both inside
	if (cutter.y < 0.0 && cutter.x > 0.0 && form.y < 0.0 && form.x > 0.0)
	{
		nx = cutterNX;
		if (cutter.x < 0.0 && cutter.y > form.y)
		{
			res.y = cutter.y;
			ny = cutterNY;
			return res;
		}
		if (cutter.x < form.x)
		{
			res.x = cutter.x;
			nx = cutterNX;

			res.y = form.x;
			ny = formNX;

			return res;
		}
		return vec2(INFINITY);
	}

	// Inside cutter
	if (cutter.y < 0.0 && form.y > 0.0)
	{
		if (form.x > cutter.x)
			return res;
		if (cutter.x < form.y)
		{
			res.x = cutter.x;
			nx = cutterNX;
			return res;
		}
		return vec2(INFINITY);
	}

	// Inside form
	if (form.x > 0.0 && form.y < 0.0 && cutter.x > 0.0)
	{
		if (cutter.x < form.x)
		{
			res.x = cutter.x;
			nx = cutterNX;
		}
		res.y = form.y;
		ny = formNY;
	}

	return res;
}

vec2 cutJustRoots(vec2 form, vec2 cutter)
{
	vec2 res = form;

	if (isinf(form.x))
		return vec2(INFINITY);

	if (form.x > 0.0 && form.y > 0.0 && cutter.x < 0.0 && cutter.y < 0.0)
		return res;

	// Both outside
	if (cutter.y > 0.0 && form.y > 0.0)
	{
		if (cutter.x < form.x && cutter.y > form.x)
			res.x = (cutter.y > form.y) ? INFINITY : cutter.y;
		if (cutter.x < form.y && cutter.x > form.x)
			res.y = cutter.x;
		return res;
	}

	if (form.x > 0.0 && form.y < 0.0 && cutter.x < 0.0)
	{
		if (cutter.x > form.y)
		{
			res.x = form.x;
			res.y = cutter.x;
			return res;
		}
	}
	// Both inside
	if (cutter.y < 0.0 && cutter.x > 0.0 && form.y < 0.0 && form.x > 0.0)
	{
		if (cutter.x < 0.0 && cutter.y > form.y)
		{
			res.y = cutter.y;
			return res;
		}
		if (cutter.x < form.x)
		{
			res.x = cutter.x;
			res.y = form.x;
			return res;
		}
		return vec2(INFINITY);
	}

	// Inside cutter
	if (cutter.y < 0.0 && form.y > 0.0)
	{
		if (form.x > cutter.x)
			return res;
		if (cutter.x < form.y)
		{
			res.x = cutter.x;
			return res;
		}
		return vec2(INFINITY);
	}

	// Inside form
	if (form.x > 0.0 && form.y < 0.0 && cutter.x > 0.0)
	{
		if (cutter.x < form.x && cutter.y > form.x)
			res.x = cutter.x;
		res.y = form.y;
	}

	return res;
}

vec2 addJustRoots(vec2 s0, vec2 s1)
{
	if ((isinf(s1.x) && !isinf(s0.x))/* || s1.x < 0.0*/)
		return s0;
	if ((isinf(s0.x) && !isinf(s1.x))/* || s0.x < 0.0*/)
		return s1;
	vec2 res;

	// Outside both
	if (s0.y > 0.0 && s1.y > 0.0)
	{
		res.x = min(s0.x, s1.x);
		res.y = max(s0.y, s1.y);
		return res;
	}

	// Inside both
	if (s0.y < 0.0 && s1.y < 0.0)
	{
		res.x = max(s0.x, s1.x);
		res.y = min(s0.y, s1.y);
		if (s1.x < 0.0 && s0.x > 0.0)
		{
			if (s1.x > s0.y && s1.y < s0.y)
				res.y = s1.y;
			else
				res.y = s0.y;
		}
		if (s0.x < 0.0 && s1.x > 0.0)
		{
			if (s0.x > s1.y && s0.y < s1.y)
				res.y = s0.y;
			else
				res.y = s1.y;
		}
		return res;
	}

	// Inside 0
	if (s0.y < 0.0 && s1.y > 0.0)
	{
		res = s0;
		if (s1.x < s0.x && s1.y > s0.x)
		{
			res.x = s1.y;
			// res.y = -1.0;
		}
		// res.y = 0;
		return res;
	}

	// Inside 1
	if (s1.y < 0.0 && s0.y > 0.0)
	{
		res = s1;
		if (s0.x < s1.x && s0.y > s1.x)
		{
			res.x = s0.y;
			// res.y = -1.0;
		}
		return res;
	}
}

#endif
