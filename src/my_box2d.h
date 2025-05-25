/*b2WorldDef *myWorld = NULL;
b2WorldId *worldId = NULL;
unsigned long lastMs = 0;

//创建一些球
void createSomeBall()
{
  b2BodyDef bodyDef = b2DefaultBodyDef(); //使用此选项初始化您的身体定义
  bodyDef.type = b2_dynamicBody; //
  bodyDef.isAwake = true;
  float r = (random() % 100) / 100.01;
  bodyDef.position = (b2Vec2){16 + r, 4.0};
  b2BodyId bodyId = b2CreateBody(*worldId, &bodyDef);

  // 摧毁一个给定id的刚体。这会摧毁附着在身体上的所有形状和关节。
  // 不要保留对关联形状和关节的引用。
  //b2DestroyBody(bodyId);
  //bodyId = b2_nullBodyId;

  b2CircleShape shape;
  shape.m_radius = 0.7 + r;

  b2FixtureDef f;
  f.shape = &shape;
  f.density = 0.5;
  f.friction = 0.4;
  f.restitution = 0.5;

  body->CreateFixture(&f);
  body->ApplyForce(b2Vec2(10 + r, 6 + r), b2Vec2(0, 0), true);

  b2Polygon box = b2MakeBox(1.0f, 1.0f);
  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.density = 1.0f;
  shapeDef.friction = 0.3f;
  b2ShapeId shapeId = b2CreatePolygonShape(bodyId, &shapeDef, &box);
}

//创造一个世界
void createSomeWorld()
{
  b2Vec2 gravity = {0.0f, -10.0f}; //重力
  *myWorld = b2DefaultWorldDef();
  myWorld->gravity = gravity;
  *worldId = b2CreateWorld(myWorld);

  b2Draw *draw = new TFTDebugDraw();
  draw->SetFlags(1);
  myWorld->SetAllowSleeping(true);
  myWorld->SetDebugDraw(draw);

  b2BodyDef groundBodyDef;
  b2Body *groundBody = myWorld->CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;

  groundBox.SetAsBox(16, .05, b2Vec2(16, 0), 0);
  groundBody->CreateFixture(&groundBox, 0.0f);

  groundBox.SetAsBox(16, .05, b2Vec2(16, 24), 0);
  groundBody->CreateFixture(&groundBox, 0.0f);

  groundBox.SetAsBox(.05, 12, b2Vec2(0, 12), 0);
  groundBody->CreateFixture(&groundBox, 0.0f);

  groundBox.SetAsBox(.05, 12, b2Vec2(32, 12), 0);
  groundBody->CreateFixture(&groundBox, 0.0f);

  for (int i = 0; i < 24; i++)
  {
    createSomeBall();
  }
}

void my_box2d_setup()
{
  createSomeWorld();
}

void my_box2d_loop()
{
  myWorld->Step(0.1, 6, 2);
  sprite.clear();
  myWorld->DebugDraw();
  sprite.pushSprite(0, 0);
  if (millis() - lastMs >= 1000)
  {
    lastMs = millis();
    float gx, gy, gz;
    imu.getAccel(&gx, &gy, &gz);
    myWorld->SetGravity(b2Vec2(-gy * 10, -gx * 10));
  }
}*/



