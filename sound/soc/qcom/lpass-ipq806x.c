/*
 * Copyright (c) 2010-2011,2013-2015 The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * lpass-ipq806x.c -- ALSA SoC CPU DAI driver for QTi LPASS
 * Splited out the IPQ8064 soc specific from lpass-cpu.c
 */

#include <linux/clk.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <sound/pcm.h>
#include <sound/soc.h>
#include <sound/soc-dai.h>

#include "lpass-lpaif-reg.h"
#include "lpass.h"

static struct snd_soc_dai_driver lpass_cpu_dai_driver = {
	.id	= LPAIF_I2S_PORT_MI2S,
	.playback = {
		.stream_name	= "lpass-cpu-playback",
		.formats	= SNDRV_PCM_FMTBIT_S16 |
					SNDRV_PCM_FMTBIT_S24 |
					SNDRV_PCM_FMTBIT_S32,
		.rates		= SNDRV_PCM_RATE_8000 |
					SNDRV_PCM_RATE_16000 |
					SNDRV_PCM_RATE_32000 |
					SNDRV_PCM_RATE_48000 |
					SNDRV_PCM_RATE_96000,
		.rate_min	= 8000,
		.rate_max	= 96000,
		.channels_min	= 1,
		.channels_max	= 8,
	},
	.probe	= &lpass_cpu_dai_probe,
	.ops    = &lpass_cpu_dai_ops,
};

int ipq806x_lpass_alloc_dma_channel(struct lpass_data *drvdata)
{
	return LPAIF_RDMA_CHAN_MI2S;
}

int ipq806x_lpass_free_dma_channel(struct lpass_data *drvdata, int chan)
{
	return 0;
}

struct lpass_variant ipq806x_data = {
	.i2sctrl_reg_base	= 0x0010,
	.i2sctrl_reg_stride	= 0x04,
	.i2s_ports		= 5,
	.irq_reg_base		= 0x3000,
	.irq_reg_stride		= 0x1000,
	.irq_ports		= 3,
	.rdma_reg_base		= 0x6000,
	.rdma_reg_stride	= 0x1000,
	.rdma_channels		= 4,
	.rdmactl_audif_start	= 4,
	.dai_driver		= &lpass_cpu_dai_driver,
	.num_dai		= 1,
	.alloc_dma_channel	= ipq806x_lpass_alloc_dma_channel,
	.free_dma_channel	= ipq806x_lpass_free_dma_channel,
};

static const struct of_device_id ipq806x_lpass_cpu_device_id[] = {
	{ .compatible = "qcom,lpass-cpu", .data = &ipq806x_data },
	{}
};
MODULE_DEVICE_TABLE(of, ipq806x_lpass_cpu_device_id);

static struct platform_driver lpass_cpu_platform_driver = {
	.driver	= {
		.name		= "lpass-cpu",
		.of_match_table	= of_match_ptr(ipq806x_lpass_cpu_device_id),
	},
	.probe	= lpass_cpu_platform_probe,
	.remove	= lpass_cpu_platform_remove,
};
module_platform_driver(lpass_cpu_platform_driver);

MODULE_DESCRIPTION("QTi LPASS CPU Driver");
MODULE_LICENSE("GPL v2");
