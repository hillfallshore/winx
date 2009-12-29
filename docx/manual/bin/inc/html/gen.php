<?php
	$env = array('base' => './', 'nsdisp' => '');
	
	foreach ($doc->sentences as $s)
	{
		if (isset($s->comment))
		{
			$comment = $s->comment;
			if (isset($comment->category))
				$env['category'] = $comment->category;
			if (isset($comment->ns))
			{
				$base = str_replace(array('::', '.', '\\'), array('/', '/', '/'), $comment->ns) . '/';
				$base = str_replace('//', '/', $base);
				@mkdir($base, 0700, true);
				$env['base'] = $base;
				$env['nsdisp'] = str_replace('/', '::', $base);
			}
			
			if (isset($comment->topic))
			{
				$topic = $comment->topic;
				if ($topic->type == "macro")
				{
					show_macro($comment, $env);
				}
			}
		}
		else
		{
			if (!isset($base))
			{
				$base = './';
			}
			if (isset($s->class))
			{
				show_class($comment, $s, $env);
			}
			else if (isset($s->global))
			{
				show_global_fn($comment, $s, $env);
			}
			unset($comment);
		}
	}
?>