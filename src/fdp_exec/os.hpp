#pragma once

#include "enums.hpp"
#include "types.hpp"

#include <functional>
#include <memory>

namespace core { struct Core; }

namespace os
{
    enum join_e
    {
        JOIN_ANY_MODE,
        JOIN_USER_MODE
    };

    struct IModule
    {
        virtual ~IModule() = default;

        using on_proc_fn   = std::function<walk_e(proc_t)>;
        using on_thread_fn = std::function<walk_e(thread_t)>;
        using on_mod_fn    = std::function<walk_e(mod_t)>;
        using on_driver_fn = std::function<walk_e(driver_t)>;

        virtual bool                proc_list       (const on_proc_fn& on_proc) = 0;
        virtual opt<proc_t>         proc_current    () = 0;
        virtual opt<proc_t>         proc_find       (const std::string& name) = 0;
        virtual opt<proc_t>         proc_find       (uint64_t pid) = 0;
        virtual opt<std::string>    proc_name       (proc_t proc) = 0;
        virtual bool                proc_is_valid   (proc_t proc) = 0;
        virtual uint64_t            proc_id         (proc_t proc) = 0;
        virtual opt<bool>           proc_is_wow64   (proc_t proc) = 0;
        virtual void                proc_join       (proc_t proc, join_e join) = 0;
        virtual opt<phy_t>          proc_resolve    (proc_t proc, uint64_t ptr) = 0;
        virtual opt<proc_t>         proc_select     (proc_t proc, uint64_t ptr) = 0;

        virtual bool            thread_list     (proc_t proc, const on_thread_fn& on_thread) = 0;
        virtual opt<thread_t>   thread_current  () = 0;
        virtual opt<proc_t>     thread_proc     (thread_t thread) = 0;
        virtual opt<uint64_t>   thread_pc       (proc_t proc, thread_t thread) = 0;
        virtual uint64_t        thread_id       (proc_t proc, thread_t thread) = 0;

        virtual bool                mod_list(proc_t proc, const on_mod_fn& on_mod) = 0;
        virtual opt<std::string>    mod_name(proc_t proc, mod_t mod) = 0;
        virtual opt<span_t>         mod_span(proc_t proc, mod_t mod) = 0;
        virtual opt<mod_t>          mod_find(proc_t proc, uint64_t addr) = 0;

        virtual bool                driver_list (const on_driver_fn& on_driver) = 0;
        virtual opt<driver_t>       driver_find (const std::string& name) = 0;
        virtual opt<std::string>    driver_name (driver_t drv) = 0;
        virtual opt<span_t>         driver_span (driver_t drv) = 0;

        virtual void debug_print() = 0;
    };

    std::unique_ptr<IModule>    make_nt     (core::Core& core);
    std::unique_ptr<IModule>    make_linux  (core::Core& core);
} // namespace os
