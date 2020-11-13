/*
 * Particle.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include <array>

class Particle {

private:
  /**
   * Position of the particle
   */
  std::array<double, 3> x;

  /**
   * Velocity of the particle
   */
  std::array<double, 3> v;

  /**
   * Force effective on this particle
   */
  std::array<double, 3> f;

  /**
   * Force which was effective on this particle
   */
  std::array<double, 3> old_f;

  /**
   * Mass of this particle
   */
  double m;

  /**
   * Type of the particle. Use it for whatever you want (e.g. to separate
   * molecules belonging to different bodies, matters, and so on)
   */
  int type;
  
    /**
   * Safe dt/2m
   */
  double dt_2m;

  /**
   * Safe (delta t)^2/2m
   */
  double dtsq_2m;

public:
  Particle(int type = 0);

  Particle(const Particle &other);

  Particle(
      // for visualization, we need always 3 coordinates
      // -> in case of 2d, we use only the first and the second
      std::array<double, 3> x_arg, std::array<double, 3> v_arg,
      double m_arg, int type = 0);

  virtual ~Particle();

  std::array<double, 3> &getX();

  std::array<double, 3> &getF();

  std::array<double, 3> &getOldF();

  std::array<double, 3> &getV();

  double getM();

  int getType();

  bool operator==(Particle &other);

  std::string toString();

  /**
   * Add force
   * @param fn
   */
  void addF(std::array<double, 3> fn);
  /**
   * Save f to old f
   */
  void saveOldF();
  
    /**
   * Set force and save previous f old_f
   * @param fn
   */
  void setF(std::array<double, 3> fn);

  /**
   * Calculate speed from t -> t+1
   */
  void calculateV();

  /**
   * Calculate Position from t -> t+1
   */
  void calculateX();
};

std::ostream &operator<<(std::ostream &stream, Particle &p);
