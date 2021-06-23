TEST_CASE("Rectangle Class parametric Contructor Test")
{
  double sample[4][2]={{-10,10},{10,10},{10,-10},{-10,-10}};
  Rectangle test=Rectangle(sample);

  CHECK(test(0,0) == -10);
  CHECK(test(0,1) == 10);
  CHECK(test(1,0) == 10);
  CHECK(test(1,1) == 10);
  CHECK(test(2,0) == 10);
  CHECK(test(2,1) == -10);
  CHECK(test(3,0) == -10);
  CHECK(test(3,1) == -10);
}

TEST_CASE("Rectangle Class non-parametric Contructor Test")
{
  Rectangle test=Rectangle();

  CHECK(test(0,0) == 0);
  CHECK(test(0,1) == 0);
  CHECK(test(1,0) == 0);
  CHECK(test(1,1) == 0);
  CHECK(test(2,0) == 0);
  CHECK(test(2,1) == 0);
  CHECK(test(3,0) == 0);
  CHECK(test(3,1) == 0);
}

TEST_CASE("Vector Translation for Rectangle class Test")
{
  double sample[4][2]={{-10,10},{10,10},{10,-10},{-10,-10}};
  Rectangle test=Rectangle(sample);

  double sample2[2]={10,-10};
  Vector<double, 2> Vec=Vector<double, 2>(sample2);

  test=test+Vec;

  CHECK(test(0,0) == 0);
  CHECK(test(0,1) == 0);
  CHECK(test(1,0) == 20);
  CHECK(test(1,1) == 0);
  CHECK(test(2,0) == 20);
  CHECK(test(2,1) == -20);
  CHECK(test(3,0) == 0);
  CHECK(test(3,1) == -20);
}

TEST_CASE("Angle Translation for Rectangle class Test")
{
  double sample[4][2]={{-10,10},{10,10},{10,-10},{-10,-10}};
  Rectangle test=Rectangle(sample);

  double Angle=90;

  test.AngleTrans(Angle*M_PI/180);

  CHECK(test(0,0) == -10);
  CHECK(test(0,1) == -10);
  CHECK(test(1,0) == -10);
  CHECK(test(1,1) == 10);
  CHECK(test(2,0) == 10);
  CHECK(test(2,1) == 10);
  CHECK(test(3,0) == 10);
  CHECK(test(3,1) == -10);

  Angle=45;

  test.AngleTrans(Angle*M_PI/180);

  CHECK(abs(test(0,0)- 0) < 0.00001 );
  CHECK(abs(test(0,1)+ 14.14213562373) < 0.00001 );
  CHECK(abs(test(1,0)+ 14.14213562373) < 0.00001 );
  CHECK(abs(test(1,1)- 0) < 0.00001 );
  CHECK(abs(test(2,0)- 0) < 0.00001 );
  CHECK(abs(test(2,1)- 14.14213562373) < 0.00001 );
  CHECK(abs(test(3,0)- 14.14213562373) < 0.00001 );
  CHECK(abs(test(3,1)- 0) < 0.00001 );
}

TEST_CASE("<< operator for Rectangle class Test")
{
  std::string expected = "-10 10 10 10 10 -10 -10 -10 -10 10";
  std::stringstream buffer, tmp;
  std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

  double sample[4][2]={{-10,10},{10,10},{10,-10},{-10,-10}};
  Rectangle test=Rectangle(sample);

  tmp << "-10 10 10 10 10 -10 -10 -10 -10 10";
  tmp >> test;

  std::cout << test;
  std::string text = tmp.str();
  std::cout.rdbuf(prevcoutbuf);

  CHECK(text == expected);
}
