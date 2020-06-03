long labs (long i) 
{
	return i < 0 ? -i : i;
}

int atoi(char * s)
{
	int rv=0; 
	char sign = 0;

	/* skip till we find either a digit or '+' or '-' */
	while (*s) 
	{
		if (*s <= '9' && *s >= '0')
			break;
		if (*s == '-' || *s == '+') 
			break;
		s++;
	}        

	if(*s == '-')sign=1;

	if (*s == '-' || *s == '+') s++;

	while (*s && *s >= '0' && *s <= '9') 
	{
		rv = (rv * 10) + (*s - '0');
		s++;
	}

	return (sign ? -rv : rv);
}
