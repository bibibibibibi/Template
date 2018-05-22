string a;
cin>>a;
transform(a.begin(),a.end(),a.begin(),::tolower);
transform(a.begin(),a.end(),a.begin(),::toupper);
