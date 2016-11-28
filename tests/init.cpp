#include <shared_ptr.cpp>
#include <catch.hpp>
#include <iostream>

SCENARIO("ctor1", "[ctor1]"){
	  shared<int> sp;
	  REQUIRE(!sp.get());
}

SCENARIO("ctor2", "[ctor2]"){
	  shared<int> sp(new int(7));
	  REQUIRE(*sp == 7);
	  REQUIRE(sp.use_count()  == 1);
}

SCENARIO("ctor3", "[ctor3]"){
	  shared<int> sp1(new int(7));
	  shared<int> sp2 = sp1;
	  REQUIRE(*sp2 == 7);
	  REQUIRE(sp2.use_count() == 2);
}

SCENARIO("ctor4", "[ctor4]"){
	  shared<int> sp1(new int(7));
	  shared<int> sp2 = std::move(sp1);
	  REQUIRE(*sp2 == 7);
	  REQUIRE(sp2.use_count() == 1);
}

SCENARIO("prisv1", "[prisv1]"){
	  shared<int> sp1(new int(7));
	  shared<int> sp2; 
	  sp2 = sp1;
	  REQUIRE(*sp2 == 7);
	  REQUIRE(sp2.use_count() == 2);
}

SCENARIO("prisv2", "[prisv2]"){
	  shared<int> sp1(new int(7));
	  shared<int> sp2;
	  sp2=std::move(sp1);
	  REQUIRE(*sp2 == 7);
	  REQUIRE(sp2.use_count() == 1);
}

SCENARIO("swap", "[swap]"){
	  shared<int> sp1(new int(7));
	  shared<int> sp2(new int(77));
	  sp1.swap(sp2);
	  REQUIRE(*sp1 == 77);
	  REQUIRE(*sp2 == 7);
}

SCENARIO("reset", "[reset]"){
	  shared<int> sp(new int(7));
	  sp.reset(nullptr);
	  REQUIRE(!sp.get());
}

SCENARIO("get", "[get]"){
	  shared<int> sp(new int(7));
	  REQUIRE(*sp.get() == 7);
}

SCENARIO("op_CTPEJlO4KA", "op_CTPEJlO4KA[]"){
	class tmp{
	public:
		int a1;
		tmp(int x) : a1(x){}
	};
	tmp a(7);
	shared<tmp> sptr1=make_shared<tmp>(std::move(a));
	REQUIRE(sptr1->a1 == 7);
}

SCENARIO("op_3BE3DO4KA", "[op_3BE3DO4KA]"){
	  shared<int> sp(new int(7));
	  REQUIRE(*sp == 7);
}

SCENARIO("countref", "[countref]"){
	  shared<int> sp1(new int(7));
	  shared<int> sp2 = sp1;
	  shared<int> sp3;
	  sp3 = sp2;
	  REQUIRE(sp2.use_count() == 3);
}

SCENARIO("make_shared", "[make_shared]"){
	int a = 7;
	shared<int> sp = make_shared<int>(std::move(a));
	REQUIRE(*sp==7);
	}

SCENARIO("test", "[test]"){
	shared<int> sptr1;
	shared<int> sptr2{ sptr1 };
	REQUIRE(sptr2.use_count()==0);
}
