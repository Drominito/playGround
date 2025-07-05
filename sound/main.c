#include <pipewire/pipewire.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <dlfcn.h>  // Für dlopen

static void registry_event_global(void *data, uint32_t id,
                uint32_t permissions, const char *type, uint32_t version,
                const struct spa_dict *props)
{
        printf("object: id:%u type:%s/%d\n", id, type, version);
}

static const struct pw_registry_events registry_events = {
        PW_VERSION_REGISTRY_EVENTS,
        .global = registry_event_global,
};

int main(int argc, char *argv[])
{
        // Setzen der Umgebungsvariable für Module
        setenv("PIPEWIRE_MODULE_DIR", "/usr/lib/pipewire-0.3", 1);
        
        pw_init(&argc, &argv);

        struct pw_main_loop *loop = pw_main_loop_new(NULL);
        if (!loop) {
                fprintf(stderr, "Error: Failed to create main loop\n");
                return 1;
        }

        struct pw_context *context = pw_context_new(pw_main_loop_get_loop(loop), NULL, 0);
        if (!context) {
                fprintf(stderr, "Error: Failed to create context (%s)\n", strerror(errno));
                pw_main_loop_destroy(loop);
                return 1;
        }

        // Debug-Ausgabe für verfügbare Module
        printf("Available modules in %s:\n", getenv("PIPEWIRE_MODULE_DIR"));
        system("ls /usr/lib/pipewire-0.3 | grep protocol-native");

        // Manuelles Laden des Native-Protokolls mit absolutem Pfad
        const char *module_path = "/usr/lib/pipewire-0.3/libpipewire-module-protocol-native.so";
        printf("Loading module: %s\n", module_path);
        
        struct pw_module *module = pw_context_load_module(context,
                module_path,  // Absoluter Pfad
                "module.protocol-native",  // Modulname
                NULL,  // Eigenschaften
                NULL   // User data
        );
        
        if (!module) {
                fprintf(stderr, "CRITICAL: Failed to load protocol-native module\n");
                fprintf(stderr, "dlopen error: %s\n", dlerror());
                fprintf(stderr, "Verify module exists: ls -l %s\n", module_path);
                pw_context_destroy(context);
                pw_main_loop_destroy(loop);
                return 1;
        }

        // Explizite Verbindungseigenschaften
        struct pw_properties *props = pw_properties_new(NULL, NULL);
        pw_properties_set(props, "remote", "pipewire-0");
        pw_properties_set(props, "local", "pipewire-client");
        

        // Ersetzen Sie die pw_context_connect()-Sektion mit:
        int sock = socket(AF_UNIX, SOCK_STREAM, 0);
        struct sockaddr_un addr = {0};
        addr.sun_family = AF_UNIX;
        strcpy(addr.sun_path, "/run/user/1001/pipewire-0");
        
        if (connect(sock, (struct sockaddr*)&addr, sizeof(addr))) {
            fprintf(stderr, "Socket connection failed: %s\n", strerror(errno));
            return 1;
        }
        
        struct pw_core *core = pw_core_new(pw_context_get_main_loop(context), NULL, 0);
        pw_context_connect_fd(core, sock);

        if (!core) {
                fprintf(stderr, "CRITICAL ERROR: Failed to connect to PipeWire (%s)\n", strerror(errno));
                
                const char *runtime_dir = getenv("XDG_RUNTIME_DIR");
                if (!runtime_dir) runtime_dir = "/run/user/1000";
                
                printf("Checking sockets in %s:\n", runtime_dir);
                system("ls -l /run/user/$(id -u)/pipewire-*");
                
                pw_context_destroy(context);
                pw_main_loop_destroy(loop);
                return 1;
        }

        struct pw_registry *registry = pw_core_get_registry(core, PW_VERSION_REGISTRY, 0);
        if (!registry) {
                fprintf(stderr, "Error: Failed to get registry\n");
                pw_core_disconnect(core);
                pw_context_destroy(context);
                pw_main_loop_destroy(loop);
                return 1;
        }

        struct spa_hook registry_listener;
        spa_zero(registry_listener);
        pw_registry_add_listener(registry, &registry_listener, &registry_events, NULL);

        printf("PipeWire connection successful! Listing objects...\n");
        pw_main_loop_run(loop);

        pw_proxy_destroy((struct pw_proxy*)registry);
        pw_core_disconnect(core);
        pw_context_destroy(context);
        pw_main_loop_destroy(loop);

        return 0;
}
