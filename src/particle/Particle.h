/*
 * Particle.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include <array>
#include <string>

#ifdef _OPENMP
#include <omp.h>
#endif
/**
 * The particle class represents a particle and it's characteristics.
 */
class Particle {

private:
  /**
   * Velocity of the particle
   */
  std::array<double, 3> v;

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
   * Time step of the simulation
   */
  double delta_t;

  /**
   * Save dt/2m
   */
  double dt_2m;

  /**
   * Save (delta t)^2/2m
   */
  double dtsq_2m;

#ifdef _OPENMP
    /**
     * Particle lock for parallelization.
     */
    omp_lock_t lock;
    std::array<std::array<double,3>, 28> threadForces = {{{0}}};
#endif
public:
  /**
   * Particle constructor which sets its type.
   * @param type Type to be set.
   * @return
   */
  Particle(int type = 0);

  /**
   * Particle constructor that copies attributes of
   * another particle to the new particle.
   * @param other The particle to be copied.
   * @return
   */
  Particle(const Particle &other);

  /**
   * Particle constructor that takes all attributes
   * of the particle as input.
   * @param x_arg Position
   * @param v_arg Velocity
   * @param m_arg Mass
   * @param type Type of particle
   * @return
   */
  Particle(
      // for visualization, we need always 3 coordinates
      // -> in case of 2d, we use only the first and the second
      std::array<double, 3> x_arg, std::array<double, 3> v_arg,
      double m_arg, double epsilon, double sigma);

  /**
   * Particle constructor for full particles state.
   * @param x Position
   * @param v Velocity
   * @param m Mass
   * @param f Current force
   * @param old_f Old force
   * @param type Type
   * @param epsilon Epsilon
   * @param sigma Sigma
   */
  Particle(
          std::array<double, 3> x, std::array<double, 3> v,
          double m, std::array<double, 3> f, std::array<double, 3> old_f,
          int type, double epsilon, double sigma);

  /*
   * Destructor of particle
   * @param
   * @return

  virtual ~Particle();
*/

  /**
   * Getter for the position of the particle (x).
   * @return x - Position
   * @param
   */
  //std::array<double, 3> &getX();

  /*
   * Getter for the force on this particle (f).
   * @return f - Force
   * @param

  std::array<double, 3> &getF();
*/
  /**
   * Getter for the previous force on this particle (old_f)
   * @return old_f - Previous Force
   */
  std::array<double, 3> &getOldF();

  /**
   * Getter for the velocity of this particle (v).
   * @return v - Velocity
   * @param
   */
  std::array<double, 3> &getV();

  /**
   * Getter for the mass of this particle (m).
   * @return m - Mass
   * @param
   */
  double getM();


  /**
   * Getter for the type of this particle.
   * @return type
   */
  int getType();
/*
  double getEpsilon();

  double getSigma();
*/
  /**
   * Operator that compares all attributes of
   * this particle with another.
   * @param other Particle to be compared to.
   * @return TRUE when all attributes are the same
   */
  bool operator==(Particle &other);

  /*
   * Represent this particle in string format.
   * @return String representation of this particle.
   * @param

  std::string toString();
    */

  /*
   * Adds force fn to current force.
   * @param fn Force to be added.
   * @return
 */
  void addF(std::array<double, 3> fn);


  /**
   * Save f to old f and set f to 0.
   * @return
   * @param
   */
  void saveOldF();

  /**
   * Calculate velocity from t -> t+1.
   * @return
   * @param
   */
  void calculateV();

  /**
   * Calculate Position from t -> t+1.
   * @param
   * @return
   */
  void calculateX();

  /**
   * Passes delta time to set dt_2m and dtsq_2m.
   * @param
   * @return
   */
  void updateDT(double delta_t);

  /**
   * Checks if particle is out of the domain.
   * @param domain_size Size of the domain.
   * @return True if particle is out.
   */
  bool isOut(std::array<double, 3> domain_size);

  /**
   * Sets the mass of the particle.
   * @param mass New mass.
   */
  void setM(double mass);

  /**
   * Apply gravitational force on the particle.
   * @param g Gravity to be applied.
   */
  void applyGravity(double g);

    /**
    * Epsilon of the particle
    */
    double epsilon;

    /**
    * Sigma of the particle
    */
    double sigma;

    /**
    * Position of the particle
    */
    std::array<double, 3> x;

    /**
     * Force effective on this particle
     */
    std::array<double, 3> f;

#ifdef _OPENMP
    void initLock();
    void destroyLock();
    void setLock();
    void unlock();
    void consolidateForces();
#endif
};
/*
std::ostream &operator<<(std::ostream &stream, Particle &p);
*/