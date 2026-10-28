#include "app_init.h"
#include "soc_osal.h"

static void wifi_sta_entry(void)
{
    osal_printk("wifi_sta_entry.\r\n");
}

/* Run the wifi_sta_entry. */
app_run(wifi_sta_entry);