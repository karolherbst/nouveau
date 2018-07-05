#ifndef __NOUVEAU_SVM_H__
#define __NOUVEAU_SVM_H__
#include <nvif/os.h>
struct drm_device;
struct drm_file;
struct nouveau_drm;

void nouveau_svm_init(struct nouveau_drm *);
void nouveau_svm_fini(struct nouveau_drm *);
void nouveau_svm_suspend(struct nouveau_drm *);
void nouveau_svm_resume(struct nouveau_drm *);

struct nouveau_svmm;

int nouveau_svmm_init(struct drm_device *, void *, struct drm_file *);
void nouveau_svmm_fini(struct nouveau_svmm **);
int nouveau_svmm_join(struct nouveau_svmm *, u64 inst);
void nouveau_svmm_part(struct nouveau_svmm *, u64 inst);
#endif
