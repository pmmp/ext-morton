<?php

/**
 * Creates a Morton code using the 32 least significant bits of two components
 * Note: Uniqueness is only guaranteed when both components are in the range -2147483648 ... 2147483657
 */
function morton2d_encode(int $x, int $y) : int{}

/**
 * Creates a Morton code using the 21 least significant bits of three components
 * Note: Uniqueness is only guaranteed when both components are in the range -1048576 ... 1048575
 */
function morton3d_encode(int $x, int $y, int $z) : int{}

/**
 * Decodes a 2D Morton code into its 32-bit components, including sign bits.
 * Note: If the inputs used more than 31 bits (excluding sign bit), the results of this function might be different than
 * the original inputs.
 *
 * @return int[]
 * @phpstan-return array{int, int}
 */
function morton2d_decode(int $morton) : array{}

/**
 * Decodes a 3D Morton code into its 21-bit components, including sign bits.
 * Note: If the inputs used more than 20 bits (excluding sign bit), the results of this function might be different than
 * the original inputs.
 *
 * @return int[]
 * @phpstan-return array{int, int, int}
 */
function morton3d_decode(int $morton) : array{}
