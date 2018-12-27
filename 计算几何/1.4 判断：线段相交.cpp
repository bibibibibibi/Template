//1.4 ÅÐ¶Ï£ºÏß¶ÎÏà½» 
bool inter(Line l1,Line l2) 
{ 
	return 
    max(l1.s.x,l1.e.x)>=min(l2.s.x,l2.e.x) &&
    max(l2.s.x,l2.e.x)>=min(l1.s.x,l1.e.x) &&
    max(l1.s.y,l1.e.y)>=min(l2.s.y,l2.e.y) &&
    max(l2.s.y,l2.e.y)>=min(l1.s.y,l1.e.y) &&
    sgn((l2.s-l1.e)^(l1.s-l1.e))*sgn((l2.e-l1.e)^(l1.s-l1.e))<=0&& 
    sgn((l1.s-l2.e)^(l2.s-l2.e))*sgn((l1.e-l2.e)^(l2.s-l2.e))<=0; 
}
