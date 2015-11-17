<h1> Microsoft's HTML Help (.chm) format</h1>
<h2> Preface</h2>
<p>
This is documentation on the .chm format used by Microsoft HTML Help.<br>
This format has been reverse engineered in the past, but as far as I<br>
know this is the first freely available documentation on it.  One<br>
Usenet message indicates that these .chm files are actually IStorage<br>
files documented in the Microsoft Platform SDK.  However, I have not<br>
been able to locate such documentation.<br>
</p>

<h3>Note</h3>

<p>
The word "section" is badly overloaded in this document.  Sorry about<br>
that.</p>

<p>
All numbers are in hexadecimal unless otherwise indicated in the<br>
text.  Except in tabular listings, this will be indicated by<br>
$ or 0x as appropriate.  All values within the file are Intel byte<br>
order (little endian) unless indicated otherwise.<br>
</p>

<h2> The overall format of a .chm file</h2>

<p>
The .chm file begins with a short ($38 byte) initial header.  This is<br>
followed by the header section table and the offset to the<br>
content. Collectively, this is the "header".<br>
<br>
</p>

<p>
The header is followed by the header sections.  There are two header<br>
sections.  One header section is the file directory, the other<br>
contains the file length and some unknown data. Immediately following<br>
the header sections is the content.<br>
</p>

<h2> The Header</h2>
<p>
The header starts with the initial header, which has the following format<br>
</p>
<pre>
0000: char[4]  'ITSF'<br>
0004: DWORD    3 (Version number)<br>
0008: DWORD    Total header length, including header section table and<br>
following data.<br>
000C: DWORD    1 (unknown)<br>
0010: DWORD    a timestamp.<br>
Considered as a big-endian DWORD, it appears to contain<br>
seconds (MSB) and fractional seconds (second byte).<br>
The third and fourth bytes may contain even more fractional<br>
bits.  The 4 least significant bits in the last byte are<br>
constant.<br>
0014: DWORD    Windows Language ID.  The two I've seen<br>
$0409 = LANG_ENGLISH/SUBLANG_ENGLISH_US<br>
$0407 = LANG_GERMAN/SUBLANG_GERMAN<br>
0018: GUID     {7C01FD10-7BAA-11D0-9E0C-00A0-C922-E6EC}<br>
0028: GUID     {7C01FD11-7BAA-11D0-9E0C-00A0-C922-E6EC}<br>
</pre>
<p>Note: a GUID is $10 bytes, arranged as 1 DWORD, 2 WORDs, and 8 BYTEs.</p>

<p>
It is followed by the header section table, which is 2 entries, where<br>
each entry is $10 bytes long and has this format:<br>
</p>

<pre>
0000: QWORD    Offset of section from beginning of file<br>
0008: QWORD    Length of section<br>
</pre>

<p>

Following the header section table is 8 bytes of additional header<br>
data.  In Version 2 files, this data is not there and the content<br>
section starts immediately after the directory.<br>
</p>
<pre>
0000: QWORD    Offset within file of content section 0<br>
</pre>

<h2>The Header Sections</h2>
<h3>Header Section 0</h3>
<p>
This section contains the total size of the file, and not much else<br>
</p>
<pre>
0000: DWORD    $01FE (unknown)<br>
0004: DWORD    0 (unknown)<br>
0008: QWORD    File Size<br>
0010: DWORD    0 (unknown)<br>
0014: DWORD    0 (unknown)<br>
</pre>

<h3>Header Section 1: The Directory Listing</h3>
<p>
The central part of the .chm file: A directory of the files and information it<br>
contains.<br>
</p>
<h4>Directory header</h4>

<p>
The directory starts with a header; its format is as follows:<br>
</p>
<pre>
0000: char[4]  'ITSP'<br>
0004: DWORD    Version number 1<br>
0008: DWORD    Length of the directory header<br>
000C: DWORD    $0a (unknown)<br>
0010: DWORD    $1000    Directory chunk size<br>
0014: DWORD    "Density" of quickref section, usually 2.<br>
0018: DWORD    Depth of the index tree<br>
1 there is no index, 2 if there is one level of PMGI<br>
chunks.<br>
001C: DWORD    Chunk number of root index chunk, -1 if there is none<br>
(though at least one file has 0 despite there being no<br>
index chunk, probably a bug.)<br>
0020: DWORD    Chunk number of first PMGL (listing) chunk<br>
0024: DWORD    Chunk number of last PMGL (listing) chunk<br>
0028: DWORD    -1 (unknown)<br>
002C: DWORD    Number of directory chunks (total)<br>
0030: DWORD    Windows language ID<br>
0034: GUID     {5D02926A-212E-11D0-9DF9-00A0C922E6EC}<br>
0044: DWORD    $54 (This is the length again)<br>
0048: DWORD    -1 (unknown)<br>
004C: DWORD    -1 (unknown)<br>
0050: DWORD    -1 (unknown)<br>
</pre>
<h4>The Listing Chunks</h4>
<p>
The header is directly followed by the directory chunks.  There are two<br>
types of directory chunks -- index chunks, and listing chunks.  The<br>
index chunk will be omitted if there is only one listing chunk.  A<br>
listing chunk has the following format:<br>
</p>
<pre>
0000: char[4]  'PMGL'<br>
0004: DWORD    Length of free space and/or quickref area at end of<br>
directory chunk<br>
0008: DWORD    Always 0.<br>
000C: DWORD    Chunk number of previous listing chunk when reading<br>
directory in sequence (-1 if this is the first listing chunk)<br>
0010: DWORD    Chunk number of next listing chunk when reading<br>
directory in sequence (-1 if this is the last listing chunk)<br>
0014: Directory listing entries (to quickref area)  Sorted by<br>
filename; the sort is case-insensitive.<br>
</pre>
<p>
The quickref area is written backwards from the end of the chunk.  One<br>
quickref entry exists for every n entries in the file, where n is<br>
calculated as 1 + (1 << quickref density).  So for density = 2, n = 5.<br>
<br>
</p>
<pre>
Chunklen-0002: WORD     Number of entries in the chunk<br>
Chunklen-0004: WORD     Offset of entry n from entry 0<br>
Chunklen-0008: WORD     Offset of entry 2n from entry 0<br>
Chunklen-000C: WORD     Offset of entry 3n from entry 0<br>
...<br>
</pre>
<p>
The format of a directory listing entry is as follows<br>
</p>
<pre>
ENCINT: length of name<br>
BYTEs: name  (UTF-8 encoded)<br>
ENCINT: content section<br>
ENCINT: offset<br>
ENCINT: length<br>
</pre>

<p>
The offset is from the beginning of the content section the file is<br>
in, after the section has been decompressed (if appropriate).  The<br>
length also refers to length of the file in the section after decompression.<br>
</p>
<p>
There are two kinds of file represented in the directory: user data and<br>
format related files.  The files which are format-related have names which begin<br>
with '::', the user data files have names which begin with "/".<br>
<br>
</p>

<h4>The Index Chunk</h4>
<p>
An index chunk has the following format<br>
</p>
<pre>
0000: char[4]  'PMGI'<br>
0004: DWORD    Length of quickref/free area at end of directory chunk<br>
0008: Directory index entries (to quickref/free area)<br>
</pre>
<p>
The quickref area in an PMGI is the same as in an PMGL<br>
</p>
<p>
The format of a directory index entry is as follows<br>
</p>
<pre>

ENCINT: length of name<br>
BYTEs: name  (UTF-8 encoded)<br>
ENCINT: directory listing chunk which starts with name<br>
</pre>
<p>
When higher-level indexes exist (when the depth of the index tree is 3 or<br>
higher), presumably the upper-level indexes will contain the numbers<br>
of lower-level index chunks rather than listing chunks<br>
</p>

<h4>Encoded Integers</h4>
<p>
An ENCINT is a variable-length integer.  The high bit of each byte<br>
indicates "continued to the next byte".  Bytes are stored most<br>
significant to least significant.  So, for example, $EA $15 is<br>
(((0xEA&amp;0x7F)&lt;&lt;7)|0x15) = 0x3515.<br>
</p>

<h2>The Content</h2>

<p>
In Version 3, the content typically immediately follows the header<br>
sections, and is at the location indicated by the DWORD following the<br>
header section table. In Version 2, the content immediately follows<br>
the header.<br>
<br>
All content section 0 locations in the directory are relative to that<br>
point.  The other content sections are stored WITHIN content section<br>
0.<br>
</p>
<h3>The Namelist file</h3>
<p>
There exists in content section 0 and in the directory a file called<br>
"::DataSpace/NameList".  This file contains the names of all the<br>
content sections.  The format is as follows:<br>
</p>
<pre>
0000: WORD     Length of file, in words<br>
0002: WORD     Number of entries in file<br>
<br>
Each entry:<br>
0000: WORD     Length of name in words, excluding terminating null<br>
0002: WORD     Double-byte characters<br>
xxxx: WORD     0<br>
</pre>
<p>
Yes, the names have a length word AND are null terminated; sort of a<br>
belt-and-suspenders approach.  The coding system is likely UTF-16 (little endian).<br>
</p>
<p>
The section names seen so far are<br>
</p>

<ul>
<li>Uncompressed</li>
<li>MSCompressed</li>
</ul>
<p>
"Uncompressed" is self-explanatory.  The section "MSCompressed" is<br>
compressed with Microsoft's LZX algorithm.<br>
</p>
<h3>The Section Data</h3>
<p>
For each section other than 0, there exists a file called<br>
'::DataSpace/Storage/&lt;Section Name&gt;/Content'.  This file contains the<br>
compressed data for the section.  So, conceptually,<br>
getting a file from a nonzero section is a multi-step process.  First<br>
you must get the content file from section 0.  Then you decompress (if<br>
appropriate) the section.  Then you get the desired file from your decompressed section.<br>
</p>
<h3>Other section format-related files</h3>

<p>
There are several other files associated with the sections<br>
</p>
<ul>
<li>
::DataSpace/Storage/&lt;SectionName&gt;/ControlData<br>
<p>
This file contains $20 bytes of information on the compression.<br>
<br>
The information is partially known:<br>
</p>
<pre>
0000: DWORD    Number of DWORDs following 'LZXC', must be 6 if version is 2<br>
0004: ASCII    'LZXC'  Compression type identifier<br>
0008: DWORD    Version (Must be <=2)<br>
000C: DWORD    The LZX reset interval<br>
0010: DWORD    The window size<br>
0014: DWORD    The cache size<br>
0018: DWORD    0 (unknown)<br>
</pre>
<p>
Reset interval, window size, and cache size are in bytes if version is<br>
1, $8000-byte blocks if version is 2.<br>
<br>
</p>
</li>
<li>::DataSpace/Storage/&lt;SectionName&gt;/SpanInfo<br>
<p>
This file contains a quadword containing the uncompressed length of<br>
the section.<br>
</p>
</li>
<li>::DataSpace/Storage/&lt;SectionName&gt;/Transform/List<br>
<p>
It appears this file was intended to contain a list of GUIDs belonging<br>
to methods of decompressing (or otherwise transforming) the section.<br>
However, it actually contains only half of the string representation<br>
of a GUID, apparently because it was sized for characters but contains<br>
wide characters.<br>
</p>
</li>
</ul>

<h2>Appendix: The Compression</h2>
<p>
The compressed sections are compressed using LZX, a compression<br>
method Microsoft also uses for its cabinet files.  To ensure this, check the<br>
second DWORD of compression info in the ControlData file for the<br>
section &mdash; it should be 'LZXC'.  To decompress, first read the file<br>
"::DataSpace/Storage/&lt;SectionName&gt;/Transform/{7FC28940-9D31-11D0-9B27-00A0C91E9C7C}/InstanceData/ResetTable".<br>
This reset table has the following format<br>
</p>
<pre>
0000: DWORD    2     unknown (possibly a version number)<br>
0004: DWORD    Number of entries in reset table<br>
0008: DWORD    8     Size of table entry (bytes)<br>
000C: DWORD    $28   Length of table header (area before table entries)<br>
0010: QWORD    Uncompressed Length<br>
0018: QWORD    Compressed Length<br>
0020: QWORD    0x8000 block size for locations below<br>
0028: QWORD    0 (zeroth entry of table)<br>
0030: QWORD    location in compressed data of 1st block boundary in<br>
uncompressed data<br>
<br>
Repeat to end of file<br>
</pre>
<p>
Now you can finally obtain the section (from its Content file).  The<br>
window size for the LZX compression is 16 (decimal) on all the files<br>
seen so far.  This is specified by the DWORD at $10 in the ControlData<br>
file (but note that DWORD gives the window size in 0x8000-byte blocks,<br>
not the LZX code for the window size)<br>
</p>
<p>

The rule that the input bit-stream is to be re-aligned to a 16-bit boundary<br>
after $8000 output characters have been processed IS in effect,<br>
despite this LZX not being part of a CAB file.  The reset table tells<br>
you when this was done, though there is no need for that<br>
during decompression; you can just keep track of the number of output<br>
characters.  Furthermore, while this does not appear to be documented<br>
in the LZX format, the uncompressed stream is padded to an $8000<br>
byte boundary.<br>
</p>
<p>
There is one change from LZX as defined by Microsoft: After each<br>
LZX reset interval (defined in the ControlData file, but in<br>
practice equal to the window size) of compressed data is<br>
processed, the LZX state is fully reset, as if an entirely new file<br>
was being encoded.  This allows semi-random access to the compressed<br>
data; you can start reading on any reset interval boundary using the<br>
reset interval size and the reset table.<br>
</p>
<p>
<em>Note:</em><br>
Earlier versions of this document stated that the reset interval only<br>
reset the Huffman tables and required outputting the 1-bit header<br>
again.  This was erroneous.  The Lempel Ziv state is reset as well.  In<br>
practice, a decoder works just as well with the incorrect assumption,<br>
but encoding a file with match positions which refer to a time before<br>
the most recent LZX reset causes crashes on decoding.<br>
<br>
<br>
Unknown end tag for </p><br>
<br>
<br>
<br>
<br>
<hr /><br>
<br>
<br>
<h2>Acknowledgements</h2>
<p>The following people in (no particular order) have submitted<br>
information which has helped correct and close the gaps in this<br>
document.</p>
<ul>
<li>Peter Ferrie (peter_ferrie at hotmail.com) <a<br>
href="<a href='http://pferrie.tripod.com'>http://pferrie.tripod.com</a>">Web Site<br>
<br>
Unknown end tag for </a><br>
<br>
</li>

<li>Pabs (pabs at zip.to) who also runs the <a href='http://savannah.nongnu.org/projects/chmspec'>CHM Spec page</a>.</li>
</ul>
<p>And others I have not been able to reach.</p>
<br>
<br>
<hr /><br>
<br>
<br>
<p>
Copyright 2001-2003 Matthew T. Russotto<br>
<br />
</p>
<p>
You may freely copy and distribute unmodified copies of this file, or<br>
copies where the only modification is a change in line endings,<br>
padding after the html end tag, coding system, or any combination<br>
thereof.  The original is in ASCII with Unix line endings.<br>
</p>