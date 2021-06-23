TEST_CASE("Vector parametrical constructor")
{
  double sample[2]={2,3};
  Vector<double, 2> vec=Vector<double, 2>(sample);

  CHECK(vec[0] == 2);
  CHECK(vec[1] == 3);
}

TEST_CASE("Vector non-parametric constructor")
{
  Vector<double, 2> vec=Vector<double, 2>();

  CHECK(vec[0] == 0);
  CHECK(vec[1] == 0);
}

TEST_CASE("<< for Vector class Test")
{
  std::string expected = "[1] [2]";
  std::stringstream buffer, tmp;
  std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());


  double check[2]={1,2};
  Vector<double, 2> vec=Vector<double, 2>(check);

  tmp << "[1] [2]";
  tmp >> vec;
  tmp << vec;

  std::cout << vec;
  std::string text = tmp.str();
  std::cout.rdbuf(prevcoutbuf);

  CHECK(text == expected);
}

TEST_CASE("Vector addition and subtraction test")
{
  double sample1[2]={5,10};
  Vector<double, 2> vec1=Vector<double, 2>(sample1);

  double sample2[2]={3,2};
  Vector<double, 2> vec2=Vector<double, 2>(sample2);

  vec1=vec1-vec2;

  CHECK(vec1[0] == 2);
  CHECK(vec1[1] == 8);

  vec1=vec1+vec2;

  CHECK(vec1[0] == 5);
  CHECK(vec1[1] == 10);
}

TEST_CASE("Vector == operator test")
{
  double sample1[2]={5,10};
  Vector<double, 2> vec1=Vector<double, 2>(sample1);

  double sample2[2]={5,10};
  Vector<double, 2> vec2=Vector<double, 2>(sample2);

  CHECK(vec1 == vec2);

}

TEST_CASE("Vector Length member function test")
{
  double sample1[3]={2,2,1};
  Vector3 vec1=Vector3(sample1);

  CHECK(vec1.Length() == 3);

}
