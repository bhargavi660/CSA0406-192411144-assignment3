#include <dlfcn.h>
#include <stdio.h>

typedef const char *(*demo_fn)(const char *);

int main(int argc, char **argv) {
    const char *path = argc > 1 ? argv[1] : "./libdemo.so";
    void *handle = dlopen(path, RTLD_NOW);
    if (!handle) {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        return 1;
    }
    dlerror();
    demo_fn fn = (demo_fn)dlsym(handle, "demo_transform");
    const char *error = dlerror();
    if (error) {
        fprintf(stderr, "dlsym failed: %s\n", error);
        dlclose(handle);
        return 1;
    }
    printf("Runtime-loaded: %s\n", fn("assignment"));
    dlclose(handle);
    return 0;
}
