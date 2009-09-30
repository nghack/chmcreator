open URL_ADDRESS,"<url.txt";

while($url=<URL_ADDRESS>){
	`neteasebook.exe $url`;
}
close URL_ADDRESS;

opendir CUR_ROOT_DIR,".";
foreach $file(readdir CUR_ROOT_DIR){
	next if $file =~/^\./;
	print "Processing Directory:$file\n";
	processDirectory($file);
}
closedir CUR_ROOT_DIR;


sub processDirectory{
	opendir CUR_DIR,$_[0];
	foreach $file(readdir CUR_DIR){
		next if $file =~/^\./;
		print "Processing $file\n";
		$param1 = $file;
		$param2 = $_[0];
		if($param1 eq "index.html"){
			processIndexFile($param1,$param2);
			processIndexFileDetails($param1,$param2);
		}else{
			if(substr($param1,0,1) ne "_"){
				processFile($param1,$param2);
				processFileDetails($param1,$param2);
			}
		}
	}
	closedir CUR_DIR;
}
sub processIndexFile{
	print "Open File ".$_[1]."/".$_[0]."\n";
	open HTML,$_[1]."/".$_[0];
	print "Open File >".$_[1]."/"."_".$_[0]."\n";
	open HTML_BLOCK,">".$_[1]."/"."_".$_[0];
	$isPrint = 0;
	while(defined($line= <HTML>)){
		if($isPrint==1){
			printf HTML_BLOCK ($line);
			if($line eq "<!-- 评论开始 -->\n"){
				$isPrint = 0;
			}
		}else{
			if($line eq "<div class=\"box_info\">\n"){
				$isPrint = 1;
				printf HTML_BLOCK ($line);
			}
		}
	}
	close HTML_BLOCK;
	close HTML;
}
sub processIndexFileDetails{
	open HTML,">".$_[1]."/".$_[0];
	open HTML_BLOCK,$_[1]."/"."_".$_[0];
	while(defined($line= <HTML_BLOCK>)){
		$_ = $line;
		s/\/book\/(section|home)\/(\d\d\d\d\d\d\d\d\d\d\d\d|0000\w\w\w\w)\///;
		s/窄屏阅读//;
		s/\>大\</\>\</;
		s/\>中\</\>\</;
		s/\>小\</\>\</;
		
		s/\>选择字号\</\>\</;
		s/\>键盘左右键\</\>\</;
		s/\>可以上下翻页\</\>\</;
		s/\.html/_b\.html/;
		
		s/0000\w\w\w\w.html/index.html/;
		$line = $_;
		printf HTML ($line)
	}
	close HTML_BLOCK;
	close HTML;
}
sub processFile{
	print "Open File ".$_[1]."/".$_[0]."\n";
	open HTML,$_[1]."/".$_[0];
	print "Open File >".$_[1]."/"."_".$_[0]."\n";
	open HTML_BLOCK,">".$_[1]."/"."_".$_[0];
	$isPrint = 0;
	while(defined($line= <HTML>)){
		if($isPrint==1){
			printf HTML_BLOCK ($line);
			if($line eq "<!-- 评论开始 -->\n"){
				$isPrint = 0;
			}
		}else{
			if($line eq "<div id=\"article\" class=\"aContent\">\n"){
				$isPrint = 1;
				printf HTML_BLOCK ($line);
			}
		}
	}
	close HTML_BLOCK;
	close HTML;
}
sub processFileDetails{
	open HTML,">".$_[1]."/".$_[0];
	open HTML_BLOCK,$_[1]."/"."_".$_[0];
	while(defined($line= <HTML_BLOCK>)){
		$_ = $line;
		s/\/book\/(section|home)\/(\d\d\d\d\d\d\d\d\d\d\d\d|0000\w\w\w\w)\///;
		s/窄屏阅读//;
		s/\>大\</\>\</;
		s/\>中\</\>\</;
		s/\>小\</\>\</;
		
		s/\>选择字号\</\>\</;
		s/\>键盘左右键\</\>\</;
		s/\>可以上下翻页\</\>\</;
		s/\>\(← →\)\</\>\</;
		
		s/0000\w\w\w\w.html/index.html/;
		$line = $_;
		printf HTML ($line)
	}
	close HTML_BLOCK;
	close HTML;
	#rm $_[1]."/"."_".$_[0];
}