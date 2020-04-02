#ifndef DLBAPROBLEM_H
#define DLBAPROBLEM_H

#include "baproblem.h"

class DLBAProblem : public BAProblem
{
public:
    DLBAProblem();
    DLBAProblem(LossType loss_type);
    DLBAProblem(size_t max_iter, double radius, LossType loss_type);
    virtual ~DLBAProblem();

protected:
    void EvaluateGradientAndDiagonal();
    bool EvaluateCauchyStep();
    bool EvaluateGaussNewtonStep();
    bool EvaluateDogLegStep();
    bool EvaluateStep();
    void EvaluateRho();
    bool StepAccept();
    virtual void Solve();

    void GetPoseDiagonal();
    void GetPointDiagonal();
    void AugmentPoseDiagonal();
    void ResetPoseDiagonal();
    void AugmentPointDiagonal();
    void ResetPointDiagonal();
    bool StopCriterionUpdate();
    bool StopCriterionRelativeCostChange();
    inline void SetRadius(double r) { radius_ = r; }
    inline void SetMaxIteration(size_t iter) { max_iteration_ = iter; }
    void Print();

private:
    size_t max_iteration_;
    double mu_;
    double min_mu_;
    double max_mu_;
    double radius_;
    double alpha_;                          // factor of the cauchy step
    double rho_;                             // step quality
    // gradient
    VecX pose_gradient_;
    VecX point_gradient_;
    VecX intrinsic_gradient_;
    VecX scaled_pose_gradient_;
    VecX scaled_point_gradient_;
    VecX scaled_intrinsic_gradient_;
    // root of hessian diagonal
    VecX pose_diagonal_;
    VecX point_diagonal_;
    VecX intrinsic_diagonal_;
    
    VecX cauchy_step_;
    VecX gauss_newton_step_;
    VecX dl_step_;
    double dl_step_norm_;
    bool evaluate_;
    double square_error_;
    double last_square_error_;
};

#endif // DLBAPROBLEM_H
