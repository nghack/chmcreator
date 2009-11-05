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
			system("hhc \"${paramName}/${paramName}.hhp\"");
		}
	}
}
closedir CUR_DIR;