/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 251 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * 
 */


#include "cs251_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs251
{
  /**  The is the constructor 
   * This is the documentation block for the constructor.
   */ 
  
  dominos_t::dominos_t()
  {
    //Ground
    /*! \var b1 
     * \brief pointer to the body ground 
     */ 
   b2Body* b1;  
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
    }
          
    //Top horizontal shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(8.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(-13.0f, 20.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    {
      b2PolygonShape shape;
      shape.SetAsBox(5.0f, 0.25f);
  
      b2BodyDef bd;
      bd.position.Set(9.0f, 19.75f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    //inclined plane
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f, b2Vec2(0.f,0.f), 7.0f);
      b2BodyDef bd;
      bd.position.Set(18.5f, 23.75f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    //Dominos
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
		
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(-14.95f + 1.0f * i, 21.25f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}

    }
      
    //Inclined planes
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f, b2Vec2(0.f,0.f), 6.0f);

      b2BodyDef bd;
      bd.position.Set(-20.0f, 15.5f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f, b2Vec2(0.f,0.f), -6.0f);

      b2BodyDef bd;
      bd.position.Set(-12.0f, 10.5f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f, b2Vec2(0.f,0.f), 6.0f);

      b2BodyDef bd;
      bd.position.Set(-20.0f, 5.5f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    //small inclined planes

    {
      b2PolygonShape shape;
      shape.SetAsBox(1.0f, 0.25f, b2Vec2(0.f,0.f), 7.0f);

      b2BodyDef bd;
      bd.position.Set(-25.0f, 18.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    {
      b2PolygonShape shape;
      shape.SetAsBox(1.0f, 0.25f, b2Vec2(0.f,0.f), -7.0f);

      b2BodyDef bd;
      bd.position.Set(-7.0f, 13.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    {
      b2PolygonShape shape;
      shape.SetAsBox(1.0f, 0.25f, b2Vec2(0.f,0.f), 7.0f);

      b2BodyDef bd;
      bd.position.Set(-25.0f, 8.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
 
    //horizontal pendulum

       {
      b2Body* b2;
     {
  b2PolygonShape shape;
  shape.SetAsBox(0.25f, 0.25f);
    
  b2BodyDef bd;
  bd.position.Set(-4.5f, 30.0f);
  b2 = m_world->CreateBody(&bd);
  b2->CreateFixture(&shape, 10.0f);
      }
  
      b2Body* b4;
      {
  b2PolygonShape shape;
  shape.SetAsBox(0.5f, 0.5f);
    
  b2BodyDef bd;
  bd.type = b2_dynamicBody;
  bd.position.Set(-4.5f, 21.0f);
  b4 = m_world->CreateBody(&bd);
  b4->CreateFixture(&shape, 2.0f);
      }
  
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-4.5f, 30.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }

          {
      b2Body* b2;
     {
  b2PolygonShape shape;
  shape.SetAsBox(0.25f, 0.25f);
    
  b2BodyDef bd;
  bd.position.Set(-2.5f, 30.0f);
  b2 = m_world->CreateBody(&bd);
  b2->CreateFixture(&shape, 10.0f);
      }
  
      b2Body* b4;
      {
  b2PolygonShape shape;
  shape.SetAsBox(0.5f, 0.5f);
    
  b2BodyDef bd;
  bd.type = b2_dynamicBody;
  bd.position.Set(-2.5f, 21.0f);
  b4 = m_world->CreateBody(&bd);
  b4->CreateFixture(&shape, 2.0f);
      }
  
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-2.5f, 30.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }

          {
      b2Body* b2;
     {
  b2PolygonShape shape;
  shape.SetAsBox(0.25f, 0.25f);
    
  b2BodyDef bd;
  bd.position.Set(-0.5f, 30.0f);
  b2 = m_world->CreateBody(&bd);
  b2->CreateFixture(&shape, 10.0f);
      }
  
      b2Body* b4;
      {
  b2PolygonShape shape;
  shape.SetAsBox(0.5f, 0.5f);
    
  b2BodyDef bd;
  bd.type = b2_dynamicBody;
  bd.position.Set(-0.5f, 21.0f);
  b4 = m_world->CreateBody(&bd);
  b4->CreateFixture(&shape, 2.0f);
      }
  
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-0.5f, 30.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }

          {
      b2Body* b2;
     {
  b2PolygonShape shape;
  shape.SetAsBox(0.25f, 0.25f);
    
  b2BodyDef bd;
  bd.position.Set(1.5f, 30.0f);
  b2 = m_world->CreateBody(&bd);
  b2->CreateFixture(&shape, 10.0f);
      }
  
      b2Body* b4;
      {
  b2PolygonShape shape;
  shape.SetAsBox(0.5f, 0.5f);
    
  b2BodyDef bd;
  bd.type = b2_dynamicBody;
  bd.position.Set(1.5f, 21.0f);
  b4 = m_world->CreateBody(&bd);
  b4->CreateFixture(&shape, 2.0f);
      }
  
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(1.5f, 30.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }
          {
      b2Body* b2;
     {
  b2PolygonShape shape;
  shape.SetAsBox(0.25f, 0.25f);
    
  b2BodyDef bd;
  bd.position.Set(3.5f, 30.0f);
  b2 = m_world->CreateBody(&bd);
  b2->CreateFixture(&shape, 10.0f);
      }
  
      b2Body* b4;
      {
  b2PolygonShape shape;
  shape.SetAsBox(0.5f, 0.5f);
    
  b2BodyDef bd;
  bd.type = b2_dynamicBody;
  bd.position.Set(3.5f, 21.0f);
  b4 = m_world->CreateBody(&bd);
  b4->CreateFixture(&shape, 2.0f);
      }
  
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(3.5f, 30.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }


 {
      b2Body* spherebody;
  
      b2CircleShape circle;
      circle.m_radius = 0.5;
  
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
  
      //for (int i = 0; i < 10; ++i)
    b2BodyDef ballbd;
    ballbd.type = b2_dynamicBody;
    ballbd.position.Set(-18.0f, 20.5f);
    spherebody = m_world->CreateBody(&ballbd);
    spherebody->CreateFixture(&ballfd);
  }

   {
      b2Body* spherebody;
  
      b2CircleShape circle;
      circle.m_radius = 1.0;
  
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 3.5f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
  
      //for (int i = 0; i < 10; ++i)
    b2BodyDef ballbd;
    ballbd.type = b2_dynamicBody;
    ballbd.position.Set(34.5f, 34.5f);
    spherebody = m_world->CreateBody(&ballbd);
    spherebody->CreateFixture(&ballfd);
  }
 
   {
     // horizontal shelf
      b2PolygonShape shape;
      shape.SetAsBox(7.0f, 0.1f);
  
      b2BodyDef bd;
      bd.position.Set(30.5f, 28.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
      //triangular wedge
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(30.5f, 28.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);
      
      //The plank on top of the wedge
      shape.SetAsBox(5.08f, 0.1f);
      b2BodyDef bd2;
      bd2.position.Set(30.5f, 29.5f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(30.5f,29.0f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);
      //box beside the see saw
      b2PolygonShape shape2;
      shape2.SetAsBox(1.0f,0.5f);
      b2BodyDef bd3;
      bd3.position.Set(24.5f, 28.5f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.1f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
     ///sphere on the box
     b2Body* spherebody;
  
      b2CircleShape circle;
      circle.m_radius = 1.0;
  
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 3.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
    ballbd.type = b2_dynamicBody;
    ballbd.position.Set(24.5f, 30.5f);
    spherebody = m_world->CreateBody(&ballbd);
    spherebody->CreateFixture(&ballfd);
    
    /*ballbd.type = b2_dynamicBody;
    ballbd.position.Set(12.5f, 7.0f);
    spherebody = m_world->CreateBody(&ballbd);
    spherebody->CreateFixture(&ballfd);  
    */
    }
    {
     // horizontal shelf
      b2PolygonShape shape;
      shape.SetAsBox(7.0f, 0.1f);
  
      b2BodyDef bd;
      bd.position.Set(30.5f, 8.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
      //triangular wedge
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(30.5f, 8.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);
      
      //The plank on top of the wedge
      shape.SetAsBox(5.08f, 0.1f);
      b2BodyDef bd2;
      bd2.position.Set(30.5f, 9.5f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(30.5f,9.0f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);
      //box beside the see saw
      b2PolygonShape shape2;
      shape2.SetAsBox(1.0f,0.5f);
      b2BodyDef bd3;
      bd3.position.Set(36.5f, 8.5f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.1f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
     ///sphere on the box
     b2Body* spherebody;
  
      b2CircleShape circle;
      circle.m_radius = 1.0;
  
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 3.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
    ballbd.type = b2_dynamicBody;
    ballbd.position.Set(36.5f, 10.5f);
    spherebody = m_world->CreateBody(&ballbd);
    spherebody->CreateFixture(&ballfd);
    
    
    }
   
    
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
