use HTML::Parser;

sub start_handler
{
	if(($_[0] eq "a"||$_[0] eq "A") ){
		print $_[1]{"href"};
		print "\n";
	}
}
sub end_handler
{
}
  
 $p = HTML::Parser->new( api_version => 3,
                         start_h => [\&start_handler, "tagname, attr"],
                         end_h   => [\&end_handler,   "tagname"],
                         marked_sections => 1,
                       );
 $p->parse_file('a.html') || die $!;
#  HTML::Parser->new(default_h => [sub { print shift }, 'text'],
 #                   comment_h => [""],
  #                 )->parse_file('0000FOce1_b.html') || die $!;
