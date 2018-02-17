/* 
 * Sample kernel loadable module code for container_of usage.
 *
 * (C) 2018 by Murat Sezgin <msezgin@iotdweb.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/slab.h>

/*
 * my_object structure.
 */
struct my_object {
	int a;
	int b;
	int c;
};

/*
 * container_test()
 *	Test function for usage of container_of macro.
 * 
 * This function is passed a pointer which points a field of
 * an allocated my_object instance and prints the address of the
 * object and its other fields.
 */
static void container_test(int *val)
{
	struct my_object *obj;

	obj = container_of(val, struct my_object, b);

	printk(KERN_INFO "obj obtained by container_of macro using &obj->b\n");
	printk(KERN_INFO "obj: %p obj->a: %d obj->b: %d obj->c: %d\n",
		obj, obj->a, obj->b, obj->c);	
}

/*
 * container_init()
 */
static int container_init(void)
{
	struct my_object *obj;

	printk(KERN_INFO "container init\n");

	/*
	 * Allocate an instance of my_object.
	 */
	obj = kmalloc(sizeof(struct my_object), GFP_KERNEL);
	if (!obj) {
		printk(KERN_WARNING "unable to allocate memory\n");
		return -1;
	}

	/*
	 * Initialize the fields of the object.
	 */
	obj->a = 5;
	obj->b = 15;
	obj->c = 25;

	printk(KERN_INFO "Allocated and initialized object\n");
	printk(KERN_INFO "obj: %p obj->a: %d obj->b: %d obj->c: %d\n",
		obj, obj->a, obj->b, obj->c);	
	
	/*
	 * Call the test function with the address of the field b.
	 */
	container_test(&obj->b);

	kfree(obj);

	return 0;
}

/*
 * container_exit()
 */
static void container_exit(void)
{
	printk(KERN_INFO "container exit\n");
}
module_init(container_init);
module_exit(container_exit);
