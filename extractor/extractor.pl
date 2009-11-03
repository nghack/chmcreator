use Digest::MD5 'md5_hex';
use Encode; 

opendir CUR_DIR,".";
foreach $file(readdir CUR_DIR){
	next if $file =~/^\./;
	$paramFullName = $file;
	$paramName = $file;
	if(length($paramFullName)>4){
		$endfix = substr($paramFullName,length($paramFullName)-4);
		if(lc($endfix) eq ".chm"){
			$paramName = substr($paramFullName,0,length($paramFullName)-4);
			print "Extracting: $paramFullName\n";
			print "extract.exe  \"$paramName\" \"$paramFullName\"";
			#system("hh -decompile \"$paramFullName\" \"./$paramName\" ");
			`extract.exe  \"$paramFullName\" \"$paramName\" `;
			
			open HHP_FILE,">${paramName}/${paramName}.hhp";
			
			print HHP_FILE "[OPTIONS]\n";
			print HHP_FILE "Binary Index=false\n";
			print HHP_FILE "Binary TOC=false\n";
			print HHP_FILE "Compatibility=1.0\n";
			print HHP_FILE "Compiled file=${paramName}.chm\n";			
			print HHP_FILE "Contents file=";
			print HHP_FILE getContentFile(${paramName})."\n";
			print HHP_FILE "Default Font=MS UI Gothic,12,-1,5,50,0,0,0,0,0\n";
			print HHP_FILE "Default topic=";
			print HHP_FILE getDefaultFile(${paramName})."\n";
			print HHP_FILE "Display compile progress=Yes\n";
			print HHP_FILE "Enhanced decompilation=false\n";
			print HHP_FILE "Error log file=log.txt\n";
			print HHP_FILE "Flat=false\n";
			print HHP_FILE "Full-text search=false\n";
			
			print HHP_FILE "Index file=";
			print HHP_FILE getIndexFile(${paramName})."\n";
			print HHP_FILE "Language=0x804\n";
			print HHP_FILE "Title=${paramName} - 图书之家制作\n";
			
			close HHP_FILE;
			#system("hhc \"${paramName}/${paramName}.hhp\"");
		}
	}
}
closedir CUR_DIR;

close ANT_GODE;

sub toUTF8(){
	encode("utf-8", decode("gb2312", $_[0]));
}
sub getDefaultFile{
	open url,"<$_[0]/#URLSTR";
	my $buff;
	$status=0;
	$isEnd=0;
	$result="";
	while($isEnd ne 1 and read(url, $buff, 1)){
		my $hex = unpack("H*", $buff);
		if($status eq 0){
			if($hex ne "00"){  $status=1;}		
		}
		if($status eq 1){
			if($hex eq "00"){$isEnd=1};
			if($hex ne "00"){$result=$result.pack("H*", $hex)};
		}
	}
	print $result;
	close url;
	return $result;
}
sub getContentFile{
	my @all_files = glob "$_[0]/*.hhc";
	foreach my $file (@all_files) {
		print "Content:".${file};
		${file} = substr(${file},index(${file},"/")+1);
		return ${file};
	}
}
sub getIndexFile{
	my @all_files = glob "$_[0]/*.hhk";
	foreach my $file (@all_files) {
		print "Index:".${file};
		${file} = substr(${file},index(${file},"/")+1);
		return ${file};
	}
}