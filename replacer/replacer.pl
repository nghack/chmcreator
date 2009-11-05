use Digest::MD5 'md5_hex';
use Encode; 

open KEYWORD,"keyword.txt";
@keyword=<KEYWORD>;
foreach my $key(@keyword){
	chomp($key);
}
close KEYWORD;

open REPLACE_KEYWORD,"replacekeyword.txt";
@replacekeyword=<REPLACE_KEYWORD>;
foreach my $key(@replacekeyword){
	chomp($key);
}
close REPLACE_KEYWORD;

opendir CUR_DIR,".";
foreach $file(readdir CUR_DIR){
	next if $file =~/^\./;
	$paramFullName = $file;
	$paramName = $file;
	if(length($paramFullName)>4){
		$endfix = substr($paramFullName,length($paramFullName)-4);
		if(lc($endfix) eq ".chm"){
			$paramName = substr($paramFullName,0,length($paramFullName)-4);
			replaceInDir("./".$paramName);
		}
	}
}
closedir CUR_DIR;

sub toUTF8(){
	encode("utf-8", decode("gb2312", $_[0]));
}

sub replaceInDir{
	print "Process Dir:".$_[0]."\n";
	opendir REP_DIR,"$_[0]";
	foreach $rep_file(readdir REP_DIR){
		next if $rep_file =~/^\./;
		if(-d $_[0]."/".$rep_file) {
			replaceInDir($_[0]."/".$rep_file);
		}
		if(-T $_[0]."/".$rep_file){
			replaceInFile($_[0]."/".$rep_file);
		}
	}
	closedir REP_DIR;
}

sub replaceInFile{
	print "Process File:".$_[0]."\n";
	undef $/;
	
	open TARGET_FILE,$_[0];
  $C = <TARGET_FILE>;
 	close TARGET_FILE;
 	$/="\n";
 	
 	$count=0;
	while($count<scalar(@keyword)){
		$_=$C;
		#print "Replace:".@keyword[$count]." with:".@replacekeyword[$count]."\n";
		$C =~ s/@keyword[$count]/@replacekeyword[$count]/gi;
		$count++;
	}
 	
 	open( FILE, ">$_[0]");
 
 	print FILE $C;
 	close(FILE);
}