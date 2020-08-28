#ifndef KERMMA_MACROS_H_
#define KERMMA_MACROS_H_

#define kermma_log(msg...) pr_info("kermma: "msg)
#define kermma_debug(msg...) pr_debug("kermma: "msg)
#define kermma_alert(msg...) pr_alert("kermma: "msg)

#endif  // KERMMA_MACROS_H_
