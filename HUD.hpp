class HUD 
{
public:
	HUD();
	~HUD();

	void update(double, bool);
	void reset();

	int				score;
	float			timer;
	int				hud_status;

	static int		target_score;
	static float	start_timer;

	static int		HUD_STATUS_PLAYING;
	static int		HUD_STATUS_WIN;
	static int		HUD_STATUS_LOSE;
};
