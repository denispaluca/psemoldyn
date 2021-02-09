/*
 * Particle.cpp
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#include <iostream>
#include "utils/ArrayUtils.h"
#include "Particle.h"

#ifdef WITH_LOG4CXX
    #include <log4cxx/logger.h>
    #include <log4cxx/propertyconfigurator.h>

    using namespace log4cxx;
    using namespace log4cxx::helpers;

    //static logger variable molsimLogger
    log4cxx::LoggerPtr particleLogger(log4cxx::Logger::getLogger("particle"));
#endif
#define is_aligned(POINTER, BYTE_COUNT) \
    (((uintptr_t)(const void *)(POINTER)) % (BYTE_COUNT) == 0)

Particle::Particle(const Particle &other) {
  x = other.x;
  v = other.v;
  f = other.f;
  old_f = other.old_f;
  m = other.m;
  type = other.type;
  delta_t = other.delta_t;
  dt_2m = other.dt_2m;
  dtsq_2m = other.dtsq_2m;
  epsilon = other.epsilon;
  sigma = other.sigma;
  km = other.km;
  r0 = other.r0;
  laterMembraneParticles = other.laterMembraneParticles;
  uid = other.uid;
  debug = other.debug;
  fixed = other.fixed;

#ifdef _OPENMP
  threadForces = other.threadForces;
#endif
#ifdef WITH_LOG4CXX
    LOG4CXX_INFO(particleLogger, "Particle generated by copy!");
#endif
//#ifdef _OPENMP
//    threadForces = new std::array<double, 224>;
//    *threadForces = {0};
//#endif
}


// Todo: maybe use initializater list instead of copy?
Particle::Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg,
                   double m_arg, double epsilon, double sigma) {
  x = x_arg;
  v = v_arg;
  m = m_arg;
  type = 0;
  this->epsilon = epsilon;
  this->sigma = sigma;
  f = {0., 0., 0.};
  old_f = {0., 0., 0.};
  delta_t = 0;
  dt_2m = 0;
  uid = (int) rand();
  dtsq_2m = 0;
  debug = -1;
  r0 = -1;

#ifdef _OPENMP
    threadForces = static_cast<std::array<std::array<double, 8>, 28> *>(aligned_alloc(64, 28 * sizeof(std::array<double, 8>)));
    //threadForces[i] = new PaddedForce;
    for(auto &fn: *threadForces){
        fn = {0};
        if(!is_aligned(&fn, 64))
            std::cout<<"Not aligned "<<&fn<<"\n";
    }
#endif
#ifdef WITH_LOG4CXX
    LOG4CXX_INFO(particleLogger, "Particle generated!");
#endif

}

Particle::Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg,
                   double m_arg, double epsilon, double sigma, bool fixed) {
    x = x_arg;
    v = v_arg;
    m = m_arg;
    type = 0;
    this->epsilon = epsilon;
    this->sigma = sigma;
    f = {0., 0., 0.};
    old_f = {0., 0., 0.};
    delta_t = 0;
    dt_2m = 0;
    uid = (int) rand();
    dtsq_2m = 0;
    debug = -1;
    r0 = -1;
    this->fixed = fixed;

#ifdef _OPENMP
    threadForces = static_cast<std::array<std::array<double, 8>, 28> *>(aligned_alloc(64, 28 * sizeof(std::array<double, 8>)));
    //threadForces[i] = new PaddedForce;
    for(auto &fn: *threadForces){
        fn = {0};
        if(!is_aligned(&fn, 64))
            std::cout<<"Not aligned "<<&fn<<"\n";
    }
#endif
#ifdef WITH_LOG4CXX
    LOG4CXX_INFO(particleLogger, "Particle generated!");
#endif

}


Particle::Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg,
                   double m_arg, double epsilon, double sigma, double r0, double km, bool fixed) {
    x = x_arg;
    v = v_arg;
    m = m_arg;
    type = 0;
    this->epsilon = epsilon;
    this->sigma = sigma;
    f = {0., 0., 0.};
    old_f = {0., 0., 0.};
    delta_t = 0;
    dt_2m = 0;
    dtsq_2m = 0;
    this->r0 = r0;
    uid = (int) rand();
    this->km = km;
    debug = -1;
    this->fixed = fixed;
#ifdef WITH_LOG4CXX
    LOG4CXX_INFO(particleLogger, "Particle generated!");
#endif

}


/*
Particle::~Particle() {
#ifdef WITH_LOG4CXX
    LOG4CXX_INFO(particleLogger, "Particle destructed!");
#endif
}
 */

void Particle::updateDT(double delta_t) {
    this->delta_t = delta_t;
    dt_2m = delta_t / (2*m);
    dtsq_2m = dt_2m * delta_t;
}

//std::array<double, 3> &Particle::getX() { return x; }

std::array<double, 3> &Particle::getV() { return v; }

//std::array<double, 3> &Particle::getF() { return f; }

std::array<double, 3> &Particle::getOldF() { return old_f; }

/*
double Particle::getEpsilon() { return epsilon; }

double Particle::getSigma() { return sigma; }
*/

void Particle::saveOldF() {
  old_f = f;
  f = {0., 0., 0.};
}

double Particle::getM() { return m; }

int Particle::getType() { return type; }

/*
std::string Particle::toString() {
  std::stringstream stream;
  stream << "Particle: X:" << x << " v: " << v << " f: " << f
         << " old_f: " << old_f << " type: " << type;
  return stream.str();
}
 */

void Particle::calculateV() {
    if(!fixed) {
        for (int i = 0; i < 3; i++) {
            v[i] = v[i] + (dt_2m * (old_f[i] + f[i]));
        }
    }
}

void Particle::calculateX() {
    if (!fixed) {
        for (int i = 0; i < 3; i++) {
            x[i] = x[i] + delta_t * v[i] + dtsq_2m * f[i];
        }
    }
}

bool Particle::operator==(Particle &other) {
  return uid == other.uid;/*(&other != 0) and (x == other.x) and (v == other.v) and (f == other.f) and
         (type == other.type) and (m == other.m) and (old_f == other.old_f);*/
}

bool Particle::isOut(std::array<double, 3> domain_size) {
    return
        x[0] < 0 || x[0] > domain_size[0] ||
        x[1] < 0 || x[1] > domain_size[1] ||
        x[2] < 0 || x[2] > domain_size[2];
}

void Particle::setM(double mass) {
    this->m = mass;
}

void Particle::applyGravity(std::array<double, 3> g) {
    if (!fixed) {
        f[0] += m*g[0];
        f[1] += m*g[1];
        f[2] += m*g[2];
    }
    //addF({0, m*g, 0});
}

Particle::Particle(std::array<double, 3> x, std::array<double, 3> v, double m, std::array<double, 3> f,
                   std::array<double, 3> old_f, int type, double epsilon, double sigma, double r0, double km, bool fixed) :
                   x(x), v(v), m(m), f(f), old_f(old_f), type(type), epsilon(epsilon), sigma(sigma), r0(r0), km(km), fixed(fixed)
{
    delta_t = 0;
    dt_2m = 0;
    dtsq_2m = 0;
}

#ifdef _OPENMP
void Particle::setLock() {
    omp_set_lock(&lock);
}

void Particle::initLock() {
    omp_init_lock(&lock);
}

void Particle::destroyLock() {
    omp_destroy_lock(&lock);
}

void Particle::unlock() {
    omp_unset_lock(&lock);
}

void Particle::consolidateForces() {
    for(int i = 0; i < omp_get_max_threads(); i++){
        for(int k = 0; k < 3; k++){
            f[k] += (*threadForces)[i][k];
            (*threadForces)[i][k] = 0;
        }
    }
}

void Particle::addF(std::array<double, 3> fn) {
    auto &tf = (*threadForces)[omp_get_thread_num()];
    for(int j = 0; j < 3; j++)
        tf[j] += fn[j];
}
#endif
/*
std::ostream &operator<<(std::ostream &stream, Particle &p) {
  stream << p.toString();
  return stream;
}
*/

Particle::Particle(std::array<double, 3> x, std::array<double, 3> v, double m, std::array<double, 3> f,
                   std::array<double, 3> old_f, int type, double epsilon, double sigma, bool fixed) :
        x(x), v(v), m(m), f(f), old_f(old_f), type(type), epsilon(epsilon), sigma(sigma), fixed(fixed)
{
    delta_t = 0;
    dt_2m = 0;
    dtsq_2m = 0;
}