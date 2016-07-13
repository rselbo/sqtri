# sqtri.py A small script to calculate all Square Triangular numbers between 2 values of n
# Copyright (C) 2016 Roar Selbo
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

import os
import sys
import time

min = 1
max = 10000
calccount = 0

def main():
    print "Finding all Square triangular numbers between %d and %d" % (min, max)
    starttime = time.time()
    for n in range(min, max):
        nsq = n * n
        found, m = search(nsq, n, n * 2) #search for m between n and 2n
        if found:
            if m > 0:
                print "n %d nsq %d m %d m/n %f" % (n, nsq, m, float(m)/n)
            else:
                print "n %d nsq %d m %d m/n 0.0" % (n, nsq, m)
    elapsedtime = time.time() - starttime
    print "Calculated %d potential m values in %f seconds" % (calccount, elapsedtime)

def search(nsq, mmin, mmax):
    m = mmin + (mmax - mmin) / 2 #calculate a m value in the middle of the searchrange
    mtri = (m * (m + 1)) / 2
    global calccount
    calccount = calccount + 1
    if mtri == nsq: #we found a mach so return it
        return (True, m)
    if mmin == mmax or mmin == m: #exit case where we did not find an m value that match n squared
        return (False, 0)
    if mtri > nsq: 
        return search(nsq, mmin, m) #no match and the triangular number is larger than the n squared so we narrow the search to mmin <-> m
    return search(nsq, m, mmax) #no match and the triangular number is smaller than the n squared so we narrow the search to m <-> mmax

if __name__ == "__main__":
    args = len(sys.argv)
    if args >= 2:
        min = int(sys.argv[1])
    if args >= 3:
        max = int(sys.argv[2])
    main()