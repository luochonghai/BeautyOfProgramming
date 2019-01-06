import re
import math
from random import randint

def test_data(num):
	fir_num = randint(0,num)

	fir_part = ""
	sec_part = ""
	if fir_num:
		fir_part = str(fir_num)

	sec_len = randint(1,10)
	sec_text = 0

	for i in range(sec_len):
		sec_part += str(randint(0,9))
		if sec_text == 0 and sec_part[-1] != '0':
			sec_text = 1

	if sec_text:
		return fir_part+'('+sec_part+')'
	else:
		return fir_part

def trans_data(dat):
	res = re.search(r'\d*\(\d+\)',dat)
	fir_str = re.match(r'\d*',dat)
	fir_num = int(fir_str[0])

	if not res is None:
		sec_num = int(dat[(fir_str.span()[1]+1):-1])
		fir_deno = 10**len(fir_str[0])
		fir_gcd = int(math.gcd(fir_num,fir_deno))
		fir_num /= fir_gcd
		fir_deno /= fir_gcd

		print(sec_num)
		sec_deno = 10**(len(dat)-len(fir_str[0])-2)-1
		sec_gcd = int(math.gcd(sec_num,sec_deno))
		sec_num /= sec_gcd
		sec_deno /= sec_gcd
		sec_deno *= 10**len(fir_str[0])
		print(sec_deno*fir_deno/math.gcd(int(fir_deno),int(sec_deno)))

trans_data(test_data(5000))
