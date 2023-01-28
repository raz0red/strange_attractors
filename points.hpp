#ifndef points_hpp
#define points_hpp

const int PARTICLE_TRAIL_LENGTH = 100;

struct Coordinate3f
{
  float x;
  float y;
  float z;
};

struct ColorRGB3f
{
  float r;
  float g;
  float b;
};

class Trail
{
private:
  ColorRGB3f color;
  std::vector<Coordinate3f> coordinates;

public:
  Trail(Coordinate3f &pos, ColorRGB3f &rgb)
  {
    color = rgb;
    coordinates.push_back(pos);
  };

  // do not forget a custom copy ctor...
  Trail(const Trail &other)
  {
    color = other.color;
    coordinates = other.coordinates;
  };

  ~Trail(){};

  Coordinate3f last()
  {
    return *coordinates.end();
  };

  void update(Coordinate3f &pos)
  {
    coordinates.push_back(pos);
    // if the trail length exceeds constant, remove the first element
    if (coordinates.size() > PARTICLE_TRAIL_LENGTH)
    {
      coordinates.erase(coordinates.begin());
    }
  };

  void draw()
  {
    glColor3f(color.r, color.g, color.b);
    for (int i = 1; i < coordinates.size() - 1; i++)
    {
      glBegin(GL_LINES);
      glVertex3f(coordinates[i - 1].x, coordinates[i - 1].y, coordinates[i - 1].z);
      glVertex3f(coordinates[i].x, coordinates[i].y, coordinates[i].z);
      glEnd();
    }
  };
};

class Particle
{
  static std::set<Particle *> instances;

private:
  ColorRGB3f color;
  Coordinate3f position;
  Trail *trail;

public:
  Particle(Coordinate3f &pos, ColorRGB3f &rgb)
  {
    position = pos;
    color = rgb;
    trail = new Trail(pos, rgb);
    instances.insert(this);
  };

  // do not forget a custom copy ctor...
  Particle(const Particle &other)
  {
    position = other.position;
    color = other.color;
    trail = other.trail;
    instances.insert(this);
  }

  ~Particle()
  {
    instances.erase(this);
  }

  static const std::set<Particle *> &getInstances()
  {
    return instances;
  }

  void update(Coordinate3f &pos)
  {
    position = pos;
    trail->update(pos);
  }

  Coordinate3f getPosition()
  {
    return position;
  }

  void draw()
  {
    glColor3f(color.r, color.g, color.b);
    glPointSize(20.0f);
    glBegin(GL_POINTS);
    glVertex3f(position.x, position.y, position.z);
    glEnd();
    trail->draw();
  };
};

Coordinate3f thomas(Coordinate3f &pos)
{
  float b = 0.208186;
  float h = 0.027;
  float dt = 9.0;

  float dx = (sin(pos.y) - b * pos.x) * dt;
  float dy = (sin(pos.z) - b * pos.y) * dt;
  float dz = (sin(pos.x) - b * pos.z) * dt;

  float x = pos.x + h * dx;
  float y = pos.y + h * dy;
  float z = pos.z + h * dz;
  Coordinate3f nextCoordinate = {x, y, z};

  return nextCoordinate;
}

class ParticleSystem
{
private:
  void drawParticles()
  {
    for (Particle *particle : Particle::getInstances())
    {
      std::cout << particle->getPosition().x << std::endl;
      Coordinate3f currPos = particle->getPosition();
      Coordinate3f newPos = thomas(currPos);
      particle->update(newPos);
      particle->draw();
    }
  };

public:
  void Tick();
};

void ParticleSystem::Tick()
{
  drawParticles();
}
#endif
