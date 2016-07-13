// sqtri.py A small script to calculate all Square Triangular numbers between 2 values of n
// Copyright(C) 2016 Roar Selbo
// 
// This program is free software : you can redistribute it and / or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.If not, see < http://www.gnu.org/licenses/>.

#include <iostream>
#include <gmp.h>

mpz_t calcCount;

bool search(const mpz_t& nsq, mpz_t& mmin, mpz_t& mmax, mpz_t& m)
{
	//calculate m as mmin + ((mmax - mmin) / 2)
	mpz_t tmp;
	mpz_init(tmp);
	mpz_sub(tmp, mmax, mmin);
	mpz_div_ui(tmp, tmp, 2);
	mpz_add(m, mmin, tmp);

	mpz_t mtri;
	mpz_t mone;
	mpz_init(mtri);
	mpz_init(mone);
	mpz_add_ui(mone, m, 1); //m + 1
	mpz_mul(tmp, m, mone); //m * (m + 1)
	mpz_div_ui(mtri, tmp, 2); // (m * (m + 1)) / 2
	
	mpz_clear(tmp);
	mpz_clear(mone);

	mpz_add_ui(calcCount, calcCount, 1);

	if (mpz_cmp(mtri, nsq) == 0)
		return true;
	if(mpz_cmp(mmin, mmax) == 0 || mpz_cmp(m, mmin) == 0)
		return false;
	if (mpz_cmp(mtri, nsq) > 0)
	{
		mpz_set(mmax, m);
	}
	else
	{
		mpz_set(mmin, m);
	}
	mpz_clear(mtri);
	return search(nsq, mmin, mmax, m);
}

int main(int argc, char** argv)
{
	mpz_init(calcCount);

	const char* strmin = "0";
	const char* strmax = "100000";
	if (argc >= 2)
		strmin = argv[1];
	if (argc >= 3)
		strmax = argv[2];


	mpz_t n;
	mpz_t m;
	mpz_t nmin;
	mpz_t nmax;
	mpz_t nsq;
	mpz_init(n);
	mpz_init(m);
	mpz_init_set_str(nmin, strmin, 10);
	mpz_init_set_str(nmax, strmax, 10);
	mpz_init(nsq);

	char *strNMin = new char[mpz_sizeinbase(nmin, 10) + 2];
	char *strNMax = new char[mpz_sizeinbase(nmax, 10) + 2];;
	mpz_get_str(strNMin, 10, nmin);
	mpz_get_str(strNMax, 10, nmax);
	std::cout << "Finding all Square triangular numbers between " << strNMin << " and " << strNMax << std::endl;
	delete strNMin;
	delete strNMax;

	mpz_t mmin;
	mpz_t mmax;
	mpz_init(mmin);
	mpz_init(mmax);
	for (mpz_set(n, nmin); mpz_cmp(n, nmax) < 0; mpz_add_ui(n, n, 1))
	{
		mpz_pow_ui(nsq, n, 2);
		mpz_set(mmin, n);
		mpz_mul_ui(mmax, n, 2);
		if(search(nsq, mmin, mmax, m))
		{
			char* strN = new char[mpz_sizeinbase(n, 10) + 2];
			char* strNSq = new char[mpz_sizeinbase(nsq, 10) + 2];
			char* strM = new char[mpz_sizeinbase(m, 10) + 2];
			mpz_get_str(strN, 10, n);
			mpz_get_str(strNSq, 10, nsq);
			mpz_get_str(strM, 10, m);
			std::cout << "n " << strN << " nsq " << strNSq << " m " << strM << std::endl;
			delete strN;
			delete strNSq;
			delete strM;
		}
	}

	mpz_clear(n);
	mpz_clear(m);
	mpz_clear(mmax);
	mpz_clear(nmin);
	mpz_clear(nmax);
	mpz_clear(nsq);
	mpz_clear(mmin);
	mpz_clear(mmax);

	char* strCalcCount = new char[mpz_sizeinbase(calcCount, 10) + 2];
	mpz_get_str(strCalcCount, 10, calcCount);
	std::cout << "Calculated " << strCalcCount << " potential m values" << std::endl;
	delete strCalcCount;
	mpz_clear(calcCount);

	return 0;
}

//import os
//import sys
//import time
//
//min = 1
//max = 10000
//calccount = 0
//
//def main() :
//	print "Finding all Square triangular numbers between %d and %d" % (min, max)
//	starttime = time.time()
//	for n in range(min, max) :
//		nsq = n * n
//		found, m = search(nsq, n, n * 2) #search for m between n and 2n
//		if found:
//if m > 0:
//print "n %d nsq %d m %d m/n %f" % (n, nsq, m, float(m) / n)
//else :
//	print "n %d nsq %d m %d m/n 0.0" % (n, nsq, m)
//	elapsedtime = time.time() - starttime
//	print "Calculated %d potential m values in %f seconds" % (calccount, elapsedtime)
//
//	def search(nsq, mmin, mmax) :
//	m = mmin + (mmax - mmin) / 2 #calculate a m value in the middle of the searchrange
//	mtri = (m * (m + 1)) / 2
//	global calccount
//	calccount = calccount + 1
//	if mtri == nsq: #we found a mach so return it
//		return (True, m)
//		if mmin == mmax or mmin == m: #exit case where we did not find an m value that match n squared
//			return (False, 0)
//			if mtri > nsq:
//return search(nsq, mmin, m) #no match and the triangular number is larger than the n squared so we narrow the search to mmin < ->m
//	return search(nsq, m, mmax) #no match and the triangular number is smaller than the n squared so we narrow the search to m < ->mmax
//
//	if __name__ == "__main__":
//args = len(sys.argv)
//if args >= 2 :
//	min = int(sys.argv[1])
//	if args >= 3 :
//		max = int(sys.argv[2])
//		main()
//
//