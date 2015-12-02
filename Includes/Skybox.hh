#ifndef SKYBOX_HH_
# define SKYBOX_HH_

# include "Object.hh"

class Skybox : public Object {

private:
  std::string			_path;

  gdl::Texture			_texture1;
  gdl::Texture			_texture2;
  gdl::Texture			_texture3;
  gdl::Texture			_texture4;
  gdl::Texture			_texture5;
  gdl::Texture			_texture6;

  gdl::Geometry			_geometry1;
  gdl::Geometry			_geometry2;
  gdl::Geometry			_geometry3;
  gdl::Geometry			_geometry4;
  gdl::Geometry			_geometry5;
  gdl::Geometry			_geometry6;

public:
  Skybox(const char *);
  virtual ~Skybox();

  virtual bool initialize();
  virtual void draw(gdl::AShader &, gdl::Clock const &);

};

#endif /* !SKYBOX_HH_ */
