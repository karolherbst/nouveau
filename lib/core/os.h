/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */

#ifndef __NOUVEAU_OS_H__
#define __NOUVEAU_OS_H__

/******************************************************************************
 * bootstrap interface
 *****************************************************************************/
struct nouveau_object;

int  os_client_new(char *cfg, char *dbg, int argc, char **argv,
		   struct nouveau_object **);
void os_client_del(struct nouveau_object **);
void os_suspend(void);
void os_resume(void);
void os_backtrace(void);

/******************************************************************************
 * types
 *****************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#define u64 uint64_t
#define u32 uint32_t
#define u16 uint16_t
#define u8 uint8_t

#define s64 int64_t
#define s32 int32_t
#define s16 int16_t
#define s8 int8_t

typedef u64 dma_addr_t;
typedef dma_addr_t resource_size_t;

/******************************************************************************
 * various random macros
 *****************************************************************************/
#define noinline __attribute__ ((noinline))
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) > (b) ? (b) : (a))
#define max_t(t,a,b) max((t)(a), (t)(b))
#define min_t(t,a,b) min((t)(a), (t)(b))
#define clamp(a,b,c) min(max((a), (b)), (c))
#define roundup(a,b) ((((a) + ((b) - 1)) / (b)) * (b))
#define round_up(a,b) roundup((a), (b))
#define rounddown(a,b) ((a) / (b) * (b))
#define upper_32_bits(a) ((a) >> 32)
#define lower_32_bits(a) ((a) & 0xffffffff)
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
#define do_div(a,b) (a) = (a) / (b)
#define div_u64(a,b) (a) / (b)
#define likely(a) (a)
#define unlikely(a) (a)
#define BIT(a) (1UL << (a))

#define jiffies (ktime_to_ns(ktime_get()))
#define nsecs_to_jiffies(a) (a)
#define usecs_to_jiffies(a) nsecs_to_jiffies((a) * 1000)
#define msecs_to_jiffies(a) usecs_to_jiffies((a) * 1000)
#define HZ 1000000

#define time_before(a,b) ((a) < (b))
#define time_after_eq(a,b) ((a) >= (b))

#define THIS_MODULE 0
#define request_module(a,b,c)

#define PAGE_SHIFT 12
#define PAGE_SIZE (1 << PAGE_SHIFT)
#define PAGE_MASK (PAGE_SHIFT - 1)

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#define __acquires(a)
#define __releases(a)
#define __printf(a,b)
#define __user

static inline int
order_base_2(u64 base)
{
	u64 temp = base >> 1;
	int log2;

	for (log2 = 0; temp; log2++, temp >>= 1) {
	}

	return (base & (base - 1)) ? log2 + 1: log2;
}

/******************************************************************************
 * errno
 *****************************************************************************/

#define ENOTSUPP 524


/******************************************************************************
 * endianness
 *****************************************************************************/

#include <endian.h>

#define le16_to_cpu(a) le16toh(a)
#define le32_to_cpu(a) le32toh(a)
#define cpu_to_le16(a) htole16(a)
#define cpu_to_le32(a) htole32(a)

/******************************************************************************
 * unaligned access
 *****************************************************************************/

static inline u16
get_unaligned_le16(void *ptr)
{
	return le16_to_cpu(*(u16 *)ptr);
}

static inline u32
get_unaligned_le32(void *ptr)
{
	return le32_to_cpu(*(u32 *)ptr);
}

static inline void
put_unaligned_le16(u16 val, void *ptr)
{
	*(u16 *)ptr = cpu_to_le16(val);
}

static inline void
put_unaligned_le32(u32 val, void *ptr)
{
	*(u32 *)ptr = cpu_to_le32(val);
}

/******************************************************************************
 * bitops
 *****************************************************************************/
#define __ffs64(a) (__builtin_ffsll(a) - 1)
#define __ffs(a) (__builtin_ffs(a) - 1)
#define fls(a) ((a) ? sizeof(a) * 8 - __builtin_clz(a) : 0)

static inline int
hweight8(u32 v) {
	int i = 0;
	while (v) {
		i += (v & 1);
		v >>= 1;
	}
	return i;
}

static inline int
hweight32(u32 v) {
	int i = 0;
	while (v) {
		i += (v & 1);
		v >>= 1;
	}
	return i;
}

static inline int
test_bit(int bit, volatile unsigned long *ptr)
{
	return !!(*ptr & (1 << bit));
}

static inline int
__test_and_clear_bit(int bit, volatile unsigned long *ptr)
{
	int ret = test_bit(bit, ptr);
	*ptr &= ~(1L << bit);
	return ret;
}

static inline int
test_and_clear_bit(int bit, volatile unsigned long *ptr)
{
	return !!(__sync_fetch_and_and(ptr, ~(1L << bit)) & (1L << bit));
}

static inline int
__test_and_set_bit(int bit, volatile unsigned long *ptr)
{
	int ret = test_bit(bit, ptr);
	*ptr |= (1L << bit);
	return ret;
}

static inline int
test_and_set_bit(int bit, volatile unsigned long *ptr)
{
	 return !(__sync_fetch_and_or(ptr, (1L << bit)) & (1L << bit));
}

/******************************************************************************
 * atomics
 *****************************************************************************/
typedef struct atomic {
	int value;
} atomic_t;

#define atomic_read(a) ((a)->value)
#define atomic_set(a,b) ((a)->value = (b))
#define atomic_inc(a) ((void) __sync_fetch_and_add (&(a)->value, 1))
#define atomic_dec(a) ((void) __sync_fetch_and_add (&(a)->value, -1))
#define atomic_add(a,b) ((void) __sync_add_and_fetch(&(a)->value, (b)))
#define atomic_add_return(b,a) (__sync_add_and_fetch(&(a)->value, (b)))
#define atomic_inc_return(a) atomic_add_return(1, (a))
#define atomic_dec_return(a) atomic_add_return(-1, (a))
#define atomic_dec_and_test(a) (atomic_dec_return(a) == 0)
#define atomic_or(a,b) (void) __sync_fetch_and_or(&(b)->value, (a));
#define atomic_xchg(a,b) \
	__atomic_exchange_n(&(a)->value, (b), __ATOMIC_SEQ_CST)

/******************************************************************************
 * ktime
 *****************************************************************************/
#include <sys/time.h>

typedef struct timeval ktime_t;

static inline ktime_t
ktime_get(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv;
}

static inline s64
ktime_to_us(ktime_t kt)
{
	return kt.tv_sec * 1000000 + kt.tv_usec;
}

static inline s64
ktime_to_ns(ktime_t kt)
{
	return ktime_to_us(kt) * 1000;
}

/******************************************************************************
 * krefs
 *****************************************************************************/
struct kref {
	atomic_t refcount;
};

#define kref_init(a) atomic_set(&(a)->refcount, 1)
#define kref_get(a) atomic_inc(&(a)->refcount)
#define kref_put(a,b) if (atomic_dec_and_test(&(a)->refcount)) b(a)

/******************************************************************************
 * string
 *****************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define kstrdup(a,b) strdup((a))
#define kstrndup(a,b,c) strndup((a), (b))

static inline int
kstrtol(const char *s, unsigned int base, long *res)
{
	*res = strtol(s, NULL, base);
	if (errno && *res == LONG_MAX)
		return errno;
	if (errno && *res == 0)
		return errno;
	return 0;
}

static inline int
kstrtoul(const char *s, unsigned int base, unsigned long *res)
{
	*res = strtoul(s, NULL, base);
	if (errno && *res == ULONG_MAX)
		return errno;
	if (errno && *res == 0)
		return errno;
	return 0;
}

/******************************************************************************
 * printk
 *****************************************************************************/
#include <stdarg.h>
#include <stdio.h>

#define KERN_CRIT ""
#define KERN_ERR ""
#define KERN_WARNING ""
#define KERN_INFO ""
#define KERN_DEBUG ""

#define printk printf
#define vprintk vprintf
#define pr_cont printf

/******************************************************************************
 * memory
 *****************************************************************************/
#define GFP_KERNEL 1
#define __GFP_ZERO 2
#define GFP_DMA32  4

typedef unsigned gfp_t;

#define vmalloc malloc
#define vfree free
#define kmalloc(a,b) malloc((a))
#define kzalloc(a,b) calloc(1, (a))
#define kcalloc(a,b,c) calloc((a), (b))
#define kfree free

#define vzalloc(a) calloc(1, (a))
#define vfree free

static inline void *
kmemdup(const void *src, size_t len, gfp_t gfp)
{
	void *dst = malloc(len);
	if (dst)
		memcpy(dst, src, len);
	return dst;
}

struct page {
};

static inline struct page *
alloc_page(gfp_t gfp)
{
	return NULL;
}

static inline void
__free_page(struct page *page)
{
}

static inline dma_addr_t
page_to_phys(struct page *page)
{
	return 0;
}

static inline struct page *
pfn_to_page(dma_addr_t pfn)
{
	return NULL;
}

static inline dma_addr_t
page_to_pfn(struct page *page)
{
	return 0;
}

static inline unsigned long
get_num_physpages(void)
{
	return 0;
}

/******************************************************************************
 * assertions
 *****************************************************************************/
#include <assert.h>
#include <execinfo.h>

static inline void
nvos_backtrace(void)
{
	void *buffer[512];
	char **sinfo;
	int ninfo, i;

	ninfo = backtrace(buffer, sizeof(buffer));
	sinfo = backtrace_symbols(buffer, ninfo);
	if (sinfo) {
		for (i = 0; i < ninfo; i++)
			printf("%s\n", sinfo[i]);
		free(sinfo);
	}
}

#define BUG() do {                                                             \
	printk("BUG at %s:%d/%s()!\n\n", __FILE__, __LINE__, __func__);        \
	nvos_backtrace();                                                      \
	assert(0);                                                             \
} while(0)

#define BUG_ON(c) do { if ((c)) BUG(); } while(0)

#define WARN() do {                                                            \
	printk("WARNING at %s:%d/%s()!\n\n", __FILE__, __LINE__, __func__);    \
	nvos_backtrace();                                                      \
} while(0)

#define WARN_ON(c) (c)

/******************************************************************************
 * interrupts
 *****************************************************************************/
#define IRQF_SHARED 0

typedef enum irqreturn {
	IRQ_NONE,
	IRQ_HANDLED
} irqreturn_t;

typedef irqreturn_t (*irq_handler_t)(int, void *);

extern int  os_intr_init(unsigned int, irq_handler_t, unsigned long,
			 const char *, void *);
extern void os_intr_free(unsigned int, void *);

#define request_irq os_intr_init
#define free_irq os_intr_free

/******************************************************************************
 * spinlocks - using pthread mutex due to no static spinlock initialiser
 *****************************************************************************/
#include <pthread.h>

typedef struct spinlock_t {
	pthread_mutex_t lock;
} spinlock_t;

#define DEFINE_SPINLOCK(a) spinlock_t a = { .lock = PTHREAD_MUTEX_INITIALIZER }

#define spin_lock_init(a) pthread_mutex_init(&(a)->lock, NULL)
#define spin_lock(a) pthread_mutex_lock(&(a)->lock)
#define spin_unlock(a) pthread_mutex_unlock(&(a)->lock)
#define spin_lock_irqsave(a,b) do { (b) = 1; spin_lock((a)); } while (0)
#define spin_unlock_irqrestore(a,b) do { (void)(b); spin_unlock((a)); } while (0)

/******************************************************************************
 * rwlocks
 *****************************************************************************/
typedef struct rwlock_t {
	pthread_rwlock_t lock;
} rwlock_t;

#define rwlock_init(a) pthread_rwlock_init(&(a)->lock, NULL)
#define read_lock(a) pthread_rwlock_rdlock(&(a)->lock)
#define read_unlock(a) pthread_rwlock_unlock(&(a)->lock)
#define write_lock_irq(a) pthread_rwlock_wrlock(&(a)->lock)
#define write_unlock_irq(a) pthread_rwlock_unlock(&(a)->lock)

/******************************************************************************
 * mutexes
 *****************************************************************************/
struct mutex {
	pthread_mutex_t mutex;
};

#define DEFINE_MUTEX(a) struct mutex a = { .mutex = PTHREAD_MUTEX_INITIALIZER }
#define mutex_init(a) pthread_mutex_init(&(a)->mutex, NULL)
#define mutex_lock(a) pthread_mutex_lock(&(a)->mutex)
#define mutex_unlock(a) pthread_mutex_unlock(&(a)->mutex)

/******************************************************************************
 * lockdep
 *****************************************************************************/
struct lock_class_key {
};

#define __mutex_init(a,b,c) pthread_mutex_init(&(a)->mutex, NULL)

/******************************************************************************
 * lists
 *****************************************************************************/
#include "list.h"

/******************************************************************************
 * io space
 *****************************************************************************/
#define __iomem

void __iomem *nvos_ioremap(u64 addr, u64 size);
void  nvos_iounmap(void __iomem *ptr);

#define ioremap(a,b) nvos_ioremap((a), (b))
#define iounmap(a) nvos_iounmap((a))

#define ioread8(a) *((volatile u8 *)(a))
#define ioread16(a) *((volatile u16 *)(a))
#define ioread16_native ioread16
#define ioread32(a) *((volatile u32 *)(a))
#define ioread32_native ioread32

#define iowrite8(b,a) *((volatile u8 *)(a)) = (b)
#define iowrite16(b,a) *((volatile u16 *)(a)) = (b)
#define iowrite16_native iowrite16
#define iowrite32(b,a) *((volatile u32 *)(a)) = (b)
#define iowrite32_native iowrite32

#define memcpy_fromio memcpy
#define memcpy_toio memcpy
#define wmb()

/******************************************************************************
 * io mapping
 *****************************************************************************/
struct io_mapping {
};

static inline struct io_mapping *
io_mapping_create_wc(u64 addr, u64 size)
{
	return NULL;
}

static inline void
io_mapping_free(struct io_mapping *io)
{
}

static inline void __iomem *
io_mapping_map_atomic_wc(struct io_mapping *io, u32 offset)
{
	return NULL;
}

static inline void
io_mapping_unmap_atomic(void __iomem *p)
{
}

/******************************************************************************
 * DMI
 *****************************************************************************/
struct dmi_strmatch {
};

struct dmi_system_id {
	const char *ident;
	struct dmi_strmatch matches[4];
};

#define DMI_MATCH(a, b) { }

static inline int
dmi_check_system(const struct dmi_system_id *list)
{
	return 0;
}

/******************************************************************************
 * Device
 *****************************************************************************/
struct device_driver {
};

struct device {
	struct device_driver *driver;
};

/******************************************************************************
 * PM runtime
 *****************************************************************************/
static inline void
pm_runtime_mark_last_busy(struct device *dev)
{
}

/******************************************************************************
 * ioport
 *****************************************************************************/
struct resource {
	resource_size_t start;
	resource_size_t end;
};

#define IORESOURCE_MEM 1

static inline resource_size_t
resource_size(const struct resource *res)
{
	return res->end - res->start + 1;
}

/******************************************************************************
 * OpenFirmware
 *****************************************************************************/

struct device_node {
};

static inline const void *
of_get_property(const struct device_node *dn, const char *name, int *lenp)
{
	return NULL;
}

/******************************************************************************
 * dma-mapping
 *****************************************************************************/

static inline void *
dma_alloc_coherent(struct device *dev, size_t sz, dma_addr_t *hdl, gfp_t gfp)
{
	return NULL;
}

static inline void
dma_free_coherent(struct device *dev, size_t sz, void *vaddr, dma_addr_t bus)
{
}

/******************************************************************************
 * PCI
 *****************************************************************************/
#include <pciaccess.h>

#define PCI_DMA_BIDIRECTIONAL 1

#define PCI_CAP_ID_AGP 0x02

struct pci_dev {
	struct pci_device *pdev;
	struct device dev;
	u16 device;
	u16 subsystem_vendor;
	u16 subsystem_device;
	int irq;
};

static inline struct device_node *
pci_device_to_OF_node(const struct pci_dev *pdev)
{
	return NULL;
}

static inline int
pci_find_capability(struct pci_dev *pdev, int cap)
{
	return 0;
}

static inline int
pci_write_config_byte(struct pci_dev *pdev, int addr, u8 data)
{
	return pci_device_cfg_write_u8(pdev->pdev, data, addr);
}

static inline u64
pci_resource_start(struct pci_dev *pdev, int bar)
{
	return pdev->pdev->regions[bar].base_addr;
}

static inline u64
pci_resource_len(struct pci_dev *pdev, int bar)
{
	return pdev->pdev->regions[bar].size;
}

static inline dma_addr_t
pci_map_page(struct pci_dev *pdev, struct page *page, int offset,
	     int length, unsigned flags)
{
	return 0;
}


static inline bool
pci_dma_mapping_error(struct pci_dev *pdev, dma_addr_t addr)
{
	return true;
}

static inline void
pci_unmap_page(struct pci_dev *pdev, dma_addr_t addr, int size, unsigned flags)
{
}

static inline int
pci_enable_rom(struct pci_dev *pdev)
{
	return 0;
}

static inline void
pci_disable_rom(struct pci_dev *pdev)
{
}

static inline void __iomem *
pci_map_rom(struct pci_dev *pdev, size_t *size)
{
	void *buf;
	*size = pdev->pdev->rom_size;
	buf = malloc(*size);
	if (buf) {
		if (pci_device_read_rom(pdev->pdev, buf)) {
			free(buf);
			buf = NULL;
		}
	}
	return buf;
}

static inline void
pci_unmap_rom(struct pci_dev *pdev, void __iomem *rom)
{
	free(rom);
}

static inline void __iomem *
pci_platform_rom(struct pci_dev *pdev, size_t *size)
{
	return NULL;
}

static inline void *
pci_alloc_consistent(struct pci_dev *hwdev, size_t size,
		     dma_addr_t *dma_handle)
{
	return NULL;
}

static inline void
pci_free_consistent(struct pci_dev *hwdev, size_t size,
		    void *vaddr, dma_addr_t dma_handle)
{
}

static inline int
pci_enable_msi(struct pci_dev *pdev)
{
	return -ENOSYS;
}

static inline void
pci_disable_msi(struct pci_dev *pdev)
{
}

#define PCI_DEVFN(a,b) 0
#define pci_get_bus_and_slot(a, b) NULL
#define pci_read_config_dword(a,b,c) *(c) = 0

/******************************************************************************
 * platform device
 *****************************************************************************/

struct platform_device {
	struct device dev;
};

static inline struct resource *
platform_get_resource(struct platform_device *pdev, unsigned int type,
		      unsigned int num)
{
	return NULL;
}

static inline int
platform_get_irq_byname(struct platform_device *pdev, const char *name)
{
	return -1;
}

/******************************************************************************
 * sg table
 *****************************************************************************/
struct scatterlist {
};

struct sg_table {
	struct scatterlist *sgl;
	unsigned int nents;
};

#define for_each_sg(sglist, sg, nr, __i)	                               \
	for (__i = 0, sg = (sglist); __i < (nr); __i++, sg = sg_next(sg))
#define sg_next(a) (a)
#define sg_dma_address(a) 0ULL
#define sg_dma_len(a) 0ULL

/******************************************************************************
 * firmware
 *****************************************************************************/
#include <unistd.h>
#include <fcntl.h>

struct firmware {
	size_t size;
	void *data;
};

static inline int
request_firmware(const struct firmware **pfw, const char *name,
		 struct device *dev)
{
	struct firmware *fw = *(void **)pfw = malloc(sizeof(*fw));
	int fd = open(name, O_RDONLY);
	if (fd >= 0) {
		off_t len = lseek(fd, 0, SEEK_END);
		fw->data = malloc(len);
		fw->size = pread(fd, fw->data, len, 0);
		return 0;
	}
	free(fw);
	return errno;
}

static inline void
release_firmware(const struct firmware *fw)
{
	free(fw->data);
	free((void *)fw);
}

/******************************************************************************
 * workqueues
 *****************************************************************************/
struct work_struct;

typedef void (*work_func_t)(struct work_struct *);

struct work_struct {
	work_func_t func;
	pthread_mutex_t mutex;
	pthread_t thread;
	bool pending;
};

static inline void
INIT_WORK(struct work_struct *work, work_func_t func)
{
	pthread_mutex_init(&work->mutex, NULL);
	work->func = func;
	work->pending = false;
}

static inline void *
os_work(void *arg)
{
	struct work_struct *work = arg;
	work_func_t func;
	do {
		pthread_mutex_lock(&work->mutex);
		if (work->pending) {
			work->pending = false;
			func = work->func;
		} else {
			func = NULL;
		}
		pthread_mutex_unlock(&work->mutex);
		if (func)
			func(work);
	} while (func);
	return NULL;
}

static inline void
schedule_work(struct work_struct *work)
{
	pthread_mutex_lock(&work->mutex);
	if (!work->pending) {
		work->pending = true;
		assert(!pthread_create(&work->thread, NULL, os_work, work));
	}
	pthread_mutex_unlock(&work->mutex);
}

static inline void
flush_work(struct work_struct *work)
{
}

/******************************************************************************
 * waitqueues
 *****************************************************************************/
typedef struct __wait_queue_head {
} wait_queue_head_t;

#define init_waitqueue_head(wq)
#define wake_up(wq)
#define wake_up_all(wq)

#define wait_event(wq,cond) do {                                               \
	usleep(1);                                                             \
} while (!(cond))

#define wait_event_interruptible(wq,cond) ({                                   \
	wait_event((wq), (cond)); 0;                                           \
})

#define wait_event_timeout(wq,cond,jiffies) ({                                 \
	unsigned long _t = (jiffies) / 10000;                                  \
	do {                                                                   \
		if (cond)                                                      \
			break;                                                 \
		usleep(10);                                                    \
	} while (--_t > 0);                                                    \
	_t;                                                                    \
})

#define wait_event_interruptible_timeout(wq,cond,jiffies)                      \
	wait_event_timeout((wq), (cond), (jiffies))

/******************************************************************************
 * i2c
 *****************************************************************************/
struct i2c_adapter {
	struct {
		void *parent;
	} dev;
	const struct i2c_algorithm *algo;
	char name[48];
	void *algo_data;
	void *adapdata;
	int owner;
};

#define I2C_M_RD 1

struct i2c_msg {
	u16 addr;
	u16 flags;
	u16 len;
	u8 *buf;
};

#define I2C_FUNC_I2C 1
#define I2C_FUNC_SMBUS_EMUL 2

struct i2c_algorithm {
	int (*master_xfer)(struct i2c_adapter *, struct i2c_msg *, int);
	u32 (*functionality)(struct i2c_adapter *);
};

struct i2c_board_info {
	char type[64];
	unsigned short addr;
};

#define I2C_BOARD_INFO(a,b) .type = (a), .addr = (b)

struct i2c_client {
	struct device dev;
};

struct i2c_driver {
	struct device_driver driver;
	int (*detect)(struct i2c_client *, struct i2c_board_info *);
};

static inline struct i2c_driver *
to_i2c_driver(struct device_driver *driver)
{
	return (void *)driver;
}

static inline struct i2c_client *
i2c_new_device(struct i2c_adapter *adap, struct i2c_board_info const *info)
{
	return NULL;
}

static inline void
i2c_unregister_device(struct i2c_client *client)
{
}

static inline int
i2c_add_adapter(struct i2c_adapter *a)
{
	return 0;
}

static inline int
i2c_del_adapter(struct i2c_adapter *a)
{
	return 0;
}

static inline void *
i2c_get_adapdata(const struct i2c_adapter *a)
{
	return a->adapdata;
}

static inline void
i2c_set_adapdata(struct i2c_adapter *a, void *d)
{
	a->adapdata = d;
}

static inline int
i2c_transfer(struct i2c_adapter *a, struct i2c_msg *m, int num)
{
	if (a->algo)
		return a->algo->master_xfer(a, m, num);
	return -ENODEV;
}

/******************************************************************************
 * i2c bit-bang
 *****************************************************************************/

static struct i2c_algorithm
i2c_bit_algo = {
};

struct i2c_algo_bit_data {
	int udelay;
	unsigned long timeout;
	void *data;
	void (*setsda) (void *data, int state);
	void (*setscl) (void *data, int state);
	int  (*getsda) (void *data);
	int  (*getscl) (void *data);
	int  (*pre_xfer)(struct i2c_adapter *);
	void (*post_xfer)(struct i2c_adapter *);
};

static inline int
i2c_bit_add_bus(struct i2c_adapter *a)
{
	(void)i2c_bit_algo;
	return 0;
}

/******************************************************************************
 * delay
 *****************************************************************************/
#include <unistd.h>

#define udelay(a) usleep((a))
#define mdelay(a) usleep((a) * 1000)
#define msleep(a) usleep((a) * 1000)
#define usleep_range(a,b) usleep((a))

/******************************************************************************
 * reboot
 *****************************************************************************/
static inline int
orderly_poweroff(bool force)
{
	BUG_ON(1);
}

/******************************************************************************
 * notifier
 *****************************************************************************/
struct notifier_block {
};

/******************************************************************************
 * endianness (cont'd)
 *****************************************************************************/

#if __BYTE_ORDER == __LITTLE_ENDIAN
#undef __BIG_ENDIAN
#endif

#endif
