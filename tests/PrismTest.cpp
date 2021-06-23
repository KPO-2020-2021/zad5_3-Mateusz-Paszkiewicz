TEST_CASE("Prism constructors")
{
  double arr[12][3]={{150.707 ,156.364 ,4},{149.017 ,159.989, 4},{149.017 ,159.989, 6},{150.707, 156.364 ,6},{150.707 ,156.364 ,4},{146.722, 156.713, 4},{146.722, 156.713, 6},{150.707 ,156.364, 6},{150.707 ,156.364, 4},{148.413 ,153.087, 4},{148.413, 153.087, 6},{150.707, 156.364, 6}};
  Prism test=Prism(arr);

  CHECK(test(0,0) == 150.707);
  CHECK(test(0,1) == 156.364);
  CHECK(test(0,2) == 4);

  CHECK(test(1,0) == 149.017);
  CHECK(test(1,1) == 159.989);
  CHECK(test(1,2) == 4);

  CHECK(test(2,0) == 149.017);
  CHECK(test(2,1) == 159.989);
  CHECK(test(2,2) == 6);

  CHECK(test(3,0) == 150.707);
  CHECK(test(3,1) == 156.364);
  CHECK(test(3,2) == 6);

  CHECK(test(4,0) == 150.707);
  CHECK(test(4,1) == 156.364);
  CHECK(test(4,2) == 4);

  CHECK(test(5,0) == 146.722);
  CHECK(test(5,1) == 156.713);
  CHECK(test(5,2) == 4);

  CHECK(test(6,0) == 146.722);
  CHECK(test(6,1) == 156.713);
  CHECK(test(6,2) == 6);

  CHECK(test(7,0) == 150.707);
  CHECK(test(7,1) == 156.364);
  CHECK(test(7,2) == 6);

  CHECK(test(8,0) == 150.707);
  CHECK(test(8,1) == 156.364);
  CHECK(test(8,2) == 4);

  CHECK(test(9,0) == 148.413);
  CHECK(test(9,1) == 153.087);
  CHECK(test(9,2) == 4);

  CHECK(test(10,0) == 148.413);
  CHECK(test(10,1) == 153.087);
  CHECK(test(10,2) == 6);

  CHECK(test(11,0) == 150.707);
  CHECK(test(11,1) == 156.364);
  CHECK(test(11,2) == 6);
}

TEST_CASE("Prism Reading from file test")
{
  Prism test=Prism();

  CoordsReadFromFile("../datasets/dat_backup/PlikWlasciwy_Dron1_Rotor1.dat",test);

  CHECK(test(0,0) == 149.017);
  CHECK(test(0,1) == 159.989);
  CHECK(test(0,2) == 4);

  CHECK(test(1,0) == 149.017);
  CHECK(test(1,1) == 159.989);
  CHECK(test(1,2) == 6);

  CHECK(test(2,0) == 146.722);
  CHECK(test(2,1) == 156.713);
  CHECK(test(2,2) == 4);

  CHECK(test(3,0) == 146.722);
  CHECK(test(3,1) == 156.713);
  CHECK(test(3,2) == 6);

  CHECK(test(4,0) == 148.413);
  CHECK(test(4,1) == 153.087);
  CHECK(test(4,2) == 4);

  CHECK(test(5,0) == 148.413);
  CHECK(test(5,1) == 153.087);
  CHECK(test(5,2) == 6);

  CHECK(test(6,0) == 152.398);
  CHECK(test(6,1) == 152.739);
  CHECK(test(6,2) == 4);

  CHECK(test(7,0) == 152.398);
  CHECK(test(7,1) == 152.739);
  CHECK(test(7,2) == 6);

  CHECK(test(8,0) == 154.692);
  CHECK(test(8,1) == 156.015);
  CHECK(test(8,2) == 4);

  CHECK(test(9,0) == 154.692);
  CHECK(test(9,1) == 156.015);
  CHECK(test(9,2) == 6);

  CHECK(test(10,0) == 153.001);
  CHECK(test(10,1) == 159.641);
  CHECK(test(10,2) == 4);

  CHECK(test(11,0) == 153.001);
  CHECK(test(11,1) == 159.641);
  CHECK(test(11,2) == 6);
}

TEST_CASE("Read->Print->Read test")
{
  Prism test=Prism();

  CoordsReadFromFile("../datasets/dat_backup/PlikWlasciwy_Dron1_Rotor1.dat",test);

  SaveCoordsToFile("../datasets/dat_backup/PrismTest.txt", test);

  CoordsReadFromFile("../datasets/dat_backup/PrismTest.txt",test);

  CHECK(test(0,0) == 149.017);
  CHECK(test(0,1) == 159.989);
  CHECK(test(0,2) == 4);

  CHECK(test(1,0) == 149.017);
  CHECK(test(1,1) == 159.989);
  CHECK(test(1,2) == 6);

  CHECK(test(2,0) == 146.722);                                 //THIS TEST WAS STOPPED DUE TO
  CHECK(test(2,1) == 156.713);                                 //ROOT PRISM FILE CONSTANTLY BEING CHANGED
  CHECK(test(2,2) == 4);

  CHECK(test(3,0) == 146.722);
  CHECK(test(3,1) == 156.713);
  CHECK(test(3,2) == 6);

  CHECK(test(4,0) == 148.413);
  CHECK(test(4,1) == 153.087);
  CHECK(test(4,2) == 4);

  CHECK(test(5,0) == 148.413);
  CHECK(test(5,1) == 153.087);
  CHECK(test(5,2) == 6);

  CHECK(test(8,0) == 154.692);
  CHECK(test(8,1) == 156.015);
  CHECK(test(8,2) == 4);

  CHECK(test(9,0) == 154.692);
  CHECK(test(9,1) == 156.015);
  CHECK(test(9,2) == 6);

  CHECK(test(10,0) == 153.001);
  CHECK(test(10,1) == 159.641);
  CHECK(test(10,2) == 4);

  CHECK(test(11,0) == 153.001);
  CHECK(test(11,1) == 159.641);
  CHECK(test(11,2) == 6);

}



TEST_CASE("Prism operators")
{
  double arr[12][3]={{150.707 ,156.364 ,4},{149.017 ,159.989, 4},{149.017 ,159.989, 6},{150.707, 156.364 ,6},{150.707 ,156.364 ,4},{146.722, 156.713, 4},{146.722, 156.713, 6},{150.707 ,156.364, 6},{150.707 ,156.364, 4},{148.413 ,153.087, 4},{148.413, 153.087, 6},{150.707, 156.364, 6}};
  Prism test=Prism(arr);

  test.AngleTrans(90*M_PI/180,'z');

  CHECK(test(0,0) == -156.364);
  CHECK(test(0,1) == 150.707 );
  CHECK(test(0,2) == 4);

  CHECK(test(1,0) == -159.989);
  CHECK(test(1,1) == 149.017);
  CHECK(test(1,2) == 4);

  CHECK(test(2,0) == -159.989);
  CHECK(test(2,1) == 149.017);
  CHECK(test(2,2) == 6);

  CHECK(test(3,0) == -156.364);
  CHECK(test(3,1) == 150.707);
  CHECK(test(3,2) == 6);

  CHECK(test(4,0) == -156.364);
  CHECK(test(4,1) == 150.707);
  CHECK(test(4,2) == 4);

  CHECK(test(5,0) == -156.713);
  CHECK(test(5,1) == 146.722);
  CHECK(test(5,2) == 4);

  CHECK(test(6,0) == -156.713);
  CHECK(test(6,1) == 146.722);
  CHECK(test(6,2) == 6);

  CHECK(test(7,0) == -156.364);
  CHECK(test(7,1) == 150.707);
  CHECK(test(7,2) == 6);

  CHECK(test(8,0) == -156.364);
  CHECK(test(8,1) == 150.707);
  CHECK(test(8,2) == 4);

  CHECK(test(9,0) == -153.087);
  CHECK(test(9,1) == 148.413);
  CHECK(test(9,2) == 4);

  CHECK(test(10,0) == -153.087);
  CHECK(test(10,1) == 148.413);
  CHECK(test(10,2) == 6);

  CHECK(test(11,0) == -156.364);
  CHECK(test(11,1) == 150.707);
  CHECK(test(11,2) == 6);
}


TEST_CASE("Prism GetPosition member function")
{
  double arr[12][3]={{149.017 ,159.989, 4},{149.017 ,159.989, 4},{149.017 ,159.989, 6},
                     {150.707, 156.364 ,6},{150.707 ,156.364 ,4},{146.722, 156.713, 4},
                     {146.722, 156.713, 6},{152.398 ,152.739 ,6},{150.707 ,156.364, 4},
                     {148.413 ,153.087, 4},{148.413, 153.087, 6},{150.707, 156.364, 6}};
  Prism test=Prism(arr);

  double arr2[3]={150.7075,156.364,5};
  Vector3 Position=Vector3(arr2);


  CHECK(test.GetPosition() == Position);

}
