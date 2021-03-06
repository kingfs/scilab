// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2013 - Scilab Enterprises - Charlotte HECQUET
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
// <-- TEST WITH GRAPHIC -->
// <-- Non-regression test for bug 12150 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=12150
//
// <-- Short Description -->
//    datatipCreate fails with one single point


scf();
x=[20];
y=[190];
plot(x,y,"bo-");
e=gce();
p=e.children(1);
t=datatipCreate(p,1);
assert_checkequal(p.datatips(1).data, [20 190 0]);
assert_checkequal(p.datatips(1).text, ["X:20.0000";"Y:190.000"]);
close
