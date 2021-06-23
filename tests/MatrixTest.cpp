TEST_CASE("Matrix non-parametric Constructor test")
{
  Matrix<int, 2> mat=Matrix<int, 2>();

  CHECK(mat(0, 0) == 0);
  CHECK(mat(0, 1) == 0);
  CHECK(mat(1, 0) == 0);
  CHECK(mat(1, 1) == 0);
}

TEST_CASE("Matrix parametric Constructor test")
{
  double sample[2][2]={{1,2},{3,4}};
  Matrix<double, 2> mat=Matrix<double, 2>(sample);

  CHECK(mat(0, 0) == 1);
  CHECK(mat(0, 1) == 2);
  CHECK(mat(1, 0) == 3);
  CHECK(mat(1, 1) == 4);
}

TEST_CASE("Matrix Angle Translation Constructor test")
{
  double Translation[2][2]={{cos(0),-1*sin(0)},{sin(0),cos(0)}};
  Matrix<double, 2> mat=Matrix<double, 2>(Translation);

  CHECK(mat(0, 0) == 1);
  CHECK(mat(0, 1) == 0);
  CHECK(mat(1, 0) == 0);
  CHECK(mat(1, 1) == 1);
}

TEST_CASE("Matrix and vector multiplication test")
{
  double sample[2][2]={{1,2},{3,4}};
  Matrix<double, 2> mat=Matrix(sample);

  double sample2[2]={1,5};
  Vector<double, 2> vec=Vector<double, 2>(sample2);

  vec=mat*vec;

  CHECK(vec[0] == 11);
  CHECK(vec[1] == 23);
}

TEST_CASE("Matrix determinant evaluation with Gauss method test")
{
  double sample[3][3]={{1,2,3},{4,5,6},{7,8,10}};
  Matrix<double, 3> mat=Matrix<double, 3>(sample);

  double val;

  val=GaussMethod(mat);

  CHECK(val == -3);

}

TEST_CASE("Matrix compareson operator test")
{
  double foo[3][3]={{1,2,3},{4,5,6},{7,8,10}};
  double bar[3][3]={{1,0,0},{0,1,0},{0,0,1}};

  Matrix<double, 3> a=Matrix<double, 3>(foo);
  Matrix<double, 3> b=Matrix<double, 3>(bar);
  Matrix<double, 3> res=Matrix<double, 3>(foo);

  CHECK(res == a*b);

}

TEST_CASE("Transformation Matrix test")
{
  Matrix4x4 mat=Matrix4x4();

  double arr[]={1, 1, 1};
  Vector3 vec=Vector3(arr);

  double angle=90;
  char axis='x';

  mat.TransFill(vec, angle, axis);

  CHECK(mat(0,0)==1);
  CHECK(mat(0,1)==0);
  CHECK(mat(0,2)==0);
  CHECK(mat(0,3)==1);
  CHECK(mat(1,0)==0);
  CHECK(mat(1,1)==0);
  CHECK(mat(1,2)==-1);
  CHECK(mat(1,3)==1);
  CHECK(mat(2,0)==0);
  CHECK(mat(2,1)==1);
  CHECK(mat(2,2)==0);
  CHECK(mat(2,3)==1);
  CHECK(mat(3,0)==0);
  CHECK(mat(3,1)==0);
  CHECK(mat(3,2)==0);
  CHECK(mat(3,3)==1);


}
