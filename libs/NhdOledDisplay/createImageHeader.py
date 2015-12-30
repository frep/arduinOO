#!/usr/bin/python

import sys, getopt, re

# using PIL seems to be non-trivial... on Mac OSX this seems to do the job:
sys.path.append("/Users/frehnerp/anaconda/lib/python2.7/site-packages")
from PIL import Image

def usage():
   print "Usage:"
   print "./createImageHeader.py -i <inputfile> [-o <outputfile>]"

def main(argv):
   inputfile = ''
   outputfile = ''
   try:
      opts, args = getopt.getopt(argv,"hi:o:",["ifile=","ofile="])
   except getopt.GetoptError:
      usage()
      sys.exit(2)
   for opt, arg in opts:
      if opt == '-h':
         usage()
         sys.exit()
      elif opt in ("-i", "--ifile"):
         inputfile = arg
      elif opt in ("-o", "--ofile"):
         outputfile = arg

   if inputfile == "":
      print "inputfile not specified!"
      usage()
      sys.exit()

   try:
      img = Image.open(inputfile)
   except IOError:
      print "No such file: " + inputfile
      print "Aborted!"

   rgb_img = img.convert('RGB')

   if outputfile == "":
      ip = re.compile("(.*)\.")
      iName = ip.search(inputfile)
      outputfile = iName.group(1) + ".h"

   file = open(outputfile, 'w')
   w, h = rgb_img.size

   op = re.compile("(.*)\.")
   oName = op.search(outputfile)
   filedescription = oName.group(1).upper() + "_H_"

   file.write("#ifndef " + filedescription + "\n")
   file.write("#define " + filedescription + "\n\n")
   file.write("const unsigned char " + oName.group(1) + str(w) + "x" + str(h) + "[] = {\n")
   for y in reversed(range(h)):
      for x in range(w):
         r, g, b = rgb_img.getpixel((x, y))
         file.write("0x"+'%02x'%b+", 0x"+'%02x'%g+", 0x"+'%02x'%r+", ")
      file.write("\n")
   file.write("};\n")
   file.write("#endif /* " + filedescription + " */\n")

exit

if __name__ == "__main__":
   main(sys.argv[1:])

