#pragma once

struct ForecastObject
{
	int air_pressure_at_mean_sea_level;
	float air_temperature;
	int cloud_area_fraction;
	int cloud_base_altitude;
	int cloud_top_altitude;
	int high_type_cloud_area_fraction;
	int low_type_cloud_area_fraction;
	int medium_type_cloud_area_fraction;
	float precipitation_amount_max;
	float precipitation_amount_mean;
	float precipitation_amount_median;
	float precipitation_amount_min;
	int precipitation_frozen_part;
	int predominant_precipitation_type_at_surface;
	int probability_of_frozen_precipitation;
	int probability_of_precipitation;
	int relative_humidity;
	int symbol_code;
	int thunderstorm_probability;
	int visibility_in_air;
	int wind_from_direction;
	float wind_speed;
	float wind_speed_of_gust;
};