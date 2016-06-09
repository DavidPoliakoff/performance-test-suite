/*
 * NOTICE
 *
 * This work was produced at the Lawrence Livermore National Laboratory (LLNL)
 * under contract no. DE-AC-52-07NA27344 (Contract 44) between the U.S.
 * Department of Energy (DOE) and Lawrence Livermore National Security, LLC
 * (LLNS) for the operation of LLNL. The rights of the Federal Government are
 * reserved under Contract 44.
 *
 * DISCLAIMER
 *
 * This work was prepared as an account of work sponsored by an agency of the
 * United States Government. Neither the United States Government nor Lawrence
 * Livermore National Security, LLC nor any of their employees, makes any
 * warranty, express or implied, or assumes any liability or responsibility
 * for the accuracy, completeness, or usefulness of any information, apparatus,
 * product, or process disclosed, or represents that its use would not infringe
 * privately-owned rights. Reference herein to any specific commercial products,
 * process, or service by trade name, trademark, manufacturer or otherwise does
 * not necessarily constitute or imply its endorsement, recommendation, or
 * favoring by the United States Government or Lawrence Livermore National
 * Security, LLC. The views and opinions of authors expressed herein do not
 * necessarily state or reflect those of the United States Government or
 * Lawrence Livermore National Security, LLC, and shall not be used for
 * advertising or product endorsement purposes.
 *
 * NOTIFICATION OF COMMERCIAL USE
 *
 * Commercialization of this product is prohibited without notifying the
 * Department of Energy (DOE) or Lawrence Livermore National Security.
 */

#ifndef KRIPKE_KERNEL_H__
#define KRIPKE_KERNEL_H__

#include <Kripke.h>

struct Grid_Data;
struct SubTVec;
struct Subdomain;

/**
 * This is the Kernel base-class and interface definition.
 * This abstracts the storage of Psi, Phi, L, L+ from the rest of the code,
 * providing data-layout specific routines.
 */
class Kernel {
  public:
    explicit Kernel(Nesting_Order nest);
    virtual ~Kernel();
    virtual Nesting_Order nestingPsi(void) const = 0;
    virtual Nesting_Order nestingPhi(void) const = 0;
    virtual Nesting_Order nestingSigt(void) const = 0;
    virtual Nesting_Order nestingEll(void) const = 0;
    virtual Nesting_Order nestingEllPlus(void) const = 0;
    virtual Nesting_Order nestingSigs(void) const = 0;

    // Computational Kernels
    void LTimes(Grid_Data *grid_data);
    void LPlusTimes(Grid_Data *grid_data);
    void scattering(Grid_Data *grid_data);
    void source(Grid_Data *grid_data);
    void sweep(Grid_Data *domain, int sdom_id);
    double particleEdit(Grid_Data *domain);
  private:
    Nesting_Order nesting_order;
};


// Factory to create correct kernel object
Kernel *createKernel(Nesting_Order, int num_dims);

#endif
